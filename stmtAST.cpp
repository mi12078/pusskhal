#include <iostream>
#include <algorithm>
#include "stmtAST.hpp"
#include "symTab.hpp"

extern SymbolTable st;
extern std::ostream ostr;
extern std::map<std::string, std::stack<std::string> > varTrTable;

int labelCounter = 0;

void CompoundStmtAST::codegen() const
{
	for(auto e : _v1)
		e->codegen();
}

void MainBlockStmtAST::codegen() const
{
	ostr << "main:\n";
	ostr << "\tpush ebp\n";
	ostr << "\tmov ebp, esp\n\n";
	_stmt->codegen();
	ostr << "\n\tmov esp, ebp\n";
	ostr << "\tpop ebp\n";
	ostr << "\tret\n\n";
}

void EmptyStmtAST::codegen() const
{
}

void AssignmentStmtAST::codegen() const
{
	_rhs->codegen(R1);
	ostr << "\tmov [" <<  varTrTable[_id].top() << "], " << reg[R1] << '\n';
}

std::string AssignmentStmtAST::id() const
{
	return _id;
}

void ArrAssignmentStmtAST::codegen() const
{
}

void IfStmtAST::codegen() const
{
	int tmp = labelCounter;
	labelCounter++;
	_cond->codegen(R1);
	ostr << "\tjne L" << tmp << '\n';
	_stmt->codegen();
	ostr << "L" << tmp << ":\n";
}

void ForStmtAST::codegen() const
{
	int tmp = labelCounter;
	labelCounter += 2;

	_assign->codegen();
	ostr << "L" << tmp++ << ":\n";

	/*load var, check if it meets exit conditions, jump if so*/
	ostr << "\tmov " << reg[R1] << ", [" << _assign->id() << "]\n";
	_val->codegen(R2);
	ostr << "\tcmp " << reg[R1] << ", " << reg[R2] << '\n';
	ostr << "\tje L" << tmp << '\n';

	_stmt->codegen();

	ostr << "\tmov " << reg[R1] << ", [" << _assign->id() << "]\n";
	if(_inc)
		ostr << "\tinc " << reg[R1] << '\n';
	else
		ostr << "\tsub " << reg[R1] << '\n';
	ostr << "\tmov [" << _assign->id() << "], " << reg[R1] << '\n';

	ostr << "\tjmp L" << tmp-1 << '\n';
	ostr << "L" << tmp << ":\n";
}

void WhileStmtAST::codegen() const
{
}

void FnDeclStmtAST::codegen() const
{

	auto paramsVars = _fnVars->getVars();
	auto sep = std::find(paramsVars.begin(), paramsVars.end(),
			std::pair<std::string, TypeAST*>("", nullptr));
	auto params =
		std::vector<std::pair<std::string, TypeAST*> >(paramsVars.begin(), sep);
	auto vars =
		std::vector<std::pair<std::string, TypeAST*> >(sep+1, paramsVars.end());

	int offset = 8;
	for(auto e : params)
	{
		varTrTable[e.first].push("ebp+" + std::to_string(offset));
		offset += 4;
	}
	//originally 4, moved to 16 bcs of 4 pushes after fn prologue
	offset = 16;
	for(auto e : vars)
	{
		varTrTable[e.first].push("ebp-" + std::to_string(offset));
		offset += 4;
	}
	varTrTable[_name].push("ebp-" + std::to_string(offset));

	ostr << _name << ":\n";
	//fn prologue
	ostr << "\tpush ebp\n";
	ostr << "\tmov ebp, esp\n\n";
	//save EVERYTHING
	ostr << "\tpush edx\n";
	ostr << "\tpush ecx\n";
	ostr << "\tpush ebx\n";
	ostr << "\tpush eax\n";
	//reserving space for locals
	ostr << "\tsub esp, " << (vars.size() + 1) * 4 << '\n';
	_body->codegen();
	//deallocating local variable space
	ostr << "\tadd esp, " << (vars.size() + 1) * 4 << '\n';
	ostr << "\tmov eax, " << '[' << varTrTable[_name].top() << ']' << '\n';
	//restore saved registers
	ostr << "\tpop eax\n";
	ostr << "\tpop ebx\n";
	ostr << "\tpop ecx\n";
	ostr << "\tpop edx\n";
	//fn epilogue
	ostr << "\n\tmov esp, ebp\n";
	ostr << "\tpop ebp\n";
	ostr << "\tret\n\n";

	for(auto e : params)
		varTrTable[e.first].pop();

	for(auto e : vars)
		varTrTable[e.first].pop();
}

void FnCallStmtAST::codegen() const
{
	for(auto it=_args.rbegin(); it!=_args.rend(); ++it)
	{
		(*it)->codegen(R1);
		ostr << "\tpush " << reg[R1] << '\n';
	}
	if(_name == "writeln")
	{
		ostr << "\tpush fmt\n";
		ostr << "\tcall " <<  "printf\n";
		ostr << "\tadd esp, " << (_args.size() + 1) * 4 << '\n';
	}
	else
	{
		ostr << "\tcall " <<  _name << '\n';
		ostr << "\tadd esp, " << _args.size()*4 << '\n';
	}
}

void VarDeclStmtAST::codegen() const
{
	
	ostr << "section .bss\n";
	for(auto e : _vars)
	{
		varTrTable[e.first].push(e.first);
		ostr << e.first << ": resd 1\n";
	}
	ostr << "\nsection .text\n";
	ostr << "fmt: db \"%d\", 10, 0\n\n";
}

/**************************************************************/

int CompoundStmtAST::typeCheck() const
{
	for(auto e : _v1)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}

int MainBlockStmtAST::typeCheck() const
{
	return _stmt->typeCheck();
}

int EmptyStmtAST::typeCheck() const
{
	return T_VOID;
}

int AssignmentStmtAST::typeCheck() const
{
	TypeAST* lhs = st.searchTable(_id);
	int rhs = _rhs->typeCheck();
	if(lhs == nullptr)
	{
		std::cerr << "No symbol named " << _id << " (AssignmentStmtAST)";
		std::cerr <<  std::endl;
		return T_ERROR;
	}
	if(rhs == T_ERROR)
	{
		std::cerr << "RHS of an assignment ill-formed" << std::endl;
		return T_ERROR;
	}
	if(lhs->type() != rhs)
	{
		std::cerr << "LHS RHS type mismatch" << std::endl;
		return T_ERROR;
	}
	return T_VOID;
}

int ArrAssignmentStmtAST::typeCheck() const
{
	TypeAST* lhs = st.searchTable(_id);
	int index = _index->typeCheck();
	int rhs = _rhs->typeCheck();

	if(lhs == nullptr)
	{
		std::cerr << "No symbol named " << _id << "(ArrAssignmentStmtAST)";
		std::cerr <<  std::endl;
		return T_ERROR;
	}
	if(index != T_INTEGER)
		return T_ERROR;
	if(rhs == T_ERROR)
		return T_ERROR;
	if(lhs->type() != rhs)
		return T_ERROR;
	return T_VOID;
}

int IfStmtAST::typeCheck() const
{
	if(_cond->typeCheck() == T_ERROR)
		return T_ERROR;
	if(_stmt->typeCheck() == T_ERROR)
		return T_ERROR;
	return T_VOID;
}

int ForStmtAST::typeCheck() const
{
	if(_assign->typeCheck() == T_ERROR)
		return T_ERROR;
	if(_val->typeCheck() == T_ERROR)
		return T_ERROR;
	if(_stmt->typeCheck() == T_ERROR)
		return T_ERROR;
	return T_VOID;
}

int WhileStmtAST::typeCheck() const
{
	if(_cond->typeCheck() == T_ERROR)
		return T_ERROR;
	if(_stmt->typeCheck() == T_ERROR)
		return T_ERROR;
	return T_VOID;
}

int FnDeclStmtAST::typeCheck() const
{
	/* TODO: insert a symbol named the same as the fn, which will be
	 * used for the returning of a value
	 */
	int retVal;

	if(st.searchTable(_name))
	{
		std::cerr << "Can't declare fn " << _name;
		std::cerr << ", symbol already exists";
		std::cerr << " (FnDeclStmtAST)" << std::endl;
		return T_ERROR;
	}
	auto paramsVars = _fnVars->getVars();
	auto sep = std::find(paramsVars.begin(), paramsVars.end(),
			std::pair<std::string, TypeAST*>("", nullptr));
	auto params =
		std::vector<std::pair<std::string, TypeAST*> >(paramsVars.begin(), sep);
	auto vars =
		std::vector<std::pair<std::string, TypeAST*> >(sep+1, paramsVars.end());

	st.insertSymbol(_name, new FunctionType(_retType, params));

	paramsVars.erase(sep);

	/*placing nullptrs as a scope separator*/
	for(auto e : paramsVars)
		st.insertSymbol(e.first, nullptr);
	st.insertSymbol(_name, _retType);

	/*placing the actual symbol info*/
	if(_fnVars->typeCheck() == T_ERROR)
		return T_ERROR;

	retVal = _body->typeCheck() == T_ERROR ? T_ERROR : T_VOID;

	for(auto e : paramsVars)
		st.deleteSymbol(e.first);
	st.deleteSymbol(_name);

	paramsVars.insert(sep, std::pair<std::string, TypeAST*>("", nullptr));
	return retVal;
}

int FnCallStmtAST::typeCheck() const
{
	TypeAST* s = st.searchTable(_name);
	if(s == nullptr)
	{
		std::cerr << "No symbol named " << _name;
		std::cerr << " (FnCallStmtAST)" << std::endl;
		return T_ERROR;
	}

	auto params = dynamic_cast<FunctionType*>(s)->params();

	/*since we want writeln to have a variadic no. of args, we omit checking*/
	if(_name != "writeln")
	{
		if(params.size() != _args.size())
		{
			std::cerr << "Invalid no. of args specified";
			std::cerr << " (FnCallStmtAST)" << std::endl;
			return T_ERROR;
		}

		std::vector<ExprAST*>::const_iterator it1;
		std::vector<std::pair<std::string, TypeAST*> >::iterator it2;

		for(it1=_args.begin(), it2=params.begin(); it1!=_args.end(); ++it1, ++it2)
		{
			int arg = (*it1)->typeCheck();
			int param = it2->second->type();

			if((arg == T_ERROR) || (arg != param))
			{
				std::cerr << "Invalid argument type" << std::endl;
				std::cerr << " (FnCallStmtAST)" << std::endl;
				return T_ERROR;
			}
		}
	}
	else
	{
		std::vector<ExprAST*>::const_iterator it1;

		for(it1=_args.begin(); it1!=_args.end(); ++it1)
		{
			int arg = (*it1)->typeCheck();

			if(arg == T_ERROR)
			{
				std::cerr << "Invalid argument type" << std::endl;
				std::cerr << " (FnCallStmtAST#2)" << std::endl;
				return T_ERROR;
			}
		}
	}

	return s->type();
}

int VarDeclStmtAST::typeCheck() const
{
	for(auto e : _vars)
	{
		if(st.searchTable(e.first))
		{
			/*var with the same name has already been inserted*/
			std::cerr << "Multiple declaration of variable ";
			std::cerr <<  e.first << std::endl;
			return T_ERROR;
		}
		st.insertSymbol(e.first, e.second);
	}
}

std::vector<std::pair<std::string, TypeAST*> > VarDeclStmtAST::getVars() const
{
	return _vars;
}
