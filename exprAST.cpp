#include <iostream>
#include "exprAST.hpp"
#include "symTab.hpp"

extern SymbolTable st;
extern std::ostream ostr;
extern std::map<std::string, std::stack<std::string> > varTrTable;

void IntegerExprAST::codegen(Register dest) const
{
	ostr << "\tmov " << reg[dest] << ", "  << _val << '\n';
}

void RealExprAST::codegen(Register dest) const
{
	ostr << "\tmov " << reg[dest] << ", "  << _val << '\n';
}

void BooleanExprAST::codegen(Register dest) const
{
}

void StringExprAST::codegen(Register dest) const
{
}

void VarExprAST::codegen(Register dest) const
{
	ostr << "\tmov " << reg[dest] << ", ";
	ostr << '[' << varTrTable[_id].top()<< ']' << '\n';
}

void ArrExprAST::codegen(Register dest) const
{
}

void BinaryExprAST::codegen(Register dest) const
{
	std::string ins;

	_lhs->codegen(dest);
	_rhs->codegen(Register(dest+1));
	switch(_op)
	{
		case '+':
			ins = "add";
		break;
		case '-':
			ins = "sub";
		break;
		case '*':
			ins = "imul";
		break;
		case '=':
			ins = "cmp";
		break;
	}
	ostr << '\t' << ins << " " << reg[dest] << ", " << reg[dest+1] << '\n';
}

void UnaryExprAST::codegen(Register dest) const
{
}

void FnCallExprAST::codegen(Register dest) const
{
	//(1) Since functions always return in eax, we save the previous value
	if(dest != R1)
		ostr << "\tpush " << reg[R1] << '\n';

	for(auto it=_args.rbegin(); it!=_args.rend(); ++it)
	{
		(*it)->codegen(dest);
		ostr << "\tpush " << reg[dest] << '\n';
	}

	ostr << "\tcall " << _name << '\n';

	if(dest != R1)
		ostr << "\tmov " << reg[dest] << ", " << reg[R1] << '\n';

	ostr << "\tadd esp, " << _args.size() * 4 << '\n';

	//(2)
	if(dest != R1)
		ostr << "\tpop " << reg[R1] << '\n';
}


int IntegerExprAST::typeCheck() const
{
	return _type->type();
}

int RealExprAST::typeCheck() const
{
	return _type->type();
}

int BooleanExprAST::typeCheck() const
{
	return _type->type();
}

int StringExprAST::typeCheck() const
{
	return _type->type();
}

int VarExprAST::typeCheck() const
{
	//do we check for the existence of the variable in the symtab here?
	TypeAST* entry = st.searchTable(_id);
	if(entry)
	{
		FunctionType* ftp = dynamic_cast<FunctionType*>(entry);
		if(ftp != NULL)
		{
			if(ftp->params().size() != 0)
			{
				std::cerr << "Invalid # of arguments specified ";
				std::cerr << "(VarExprAST special case)" << std::endl;
				return T_ERROR;
			}
		}
		return entry->type();
	}
	else
	{
		std::cerr << "No symbol named " << _id << " (VarExprAST)" << std::endl;
		return T_ERROR;
	}
}

int ArrExprAST::typeCheck() const
{
	TypeAST* entry = st.searchTable(_id);
	if(entry == nullptr)
	{
		std::cerr << "No symbol named " << _id << " (ArrExprAST)" << std::endl;
		return T_ERROR;
	}
	else if(_index->typeCheck() != T_INTEGER)
	{
		std::cerr << "Array index is not an integer type" << std::endl;
		return T_ERROR;
	}

	return entry->type();
}

int BinaryExprAST::typeCheck() const
{
	int retVal;
	if((retVal = _lhs->typeCheck()) != _rhs->typeCheck())
	{
		std::cerr << "LHS RHS type mismatch (BinaryExprAST)" << std::endl;
		return T_ERROR;
	}
	if(_lhs->typeCheck() == T_ERROR || _rhs->typeCheck() == T_ERROR)
	{
		std::cerr << "Either RHS or LHS of a binary expr is ill-formed";
		std::cerr << std::endl;
		return T_ERROR;
	}
	return retVal;
}

int UnaryExprAST::typeCheck() const
{
	int retVal;
	return (retVal = _operand->typeCheck()) == T_ERROR ? T_ERROR : retVal;
}

int FnCallExprAST::typeCheck() const
{
	TypeAST* s = st.searchTable(_name);
	if(s == nullptr)
	{
		std::cerr << "No symbol named " << _name;
		std::cerr  << " (FnCallExprAST)" << std::endl;
		return T_ERROR;
	}

	auto params = dynamic_cast<FunctionType*>(s)->params();

	if(params.size() != _args.size())
	{
		std::cerr << "Invalid no. of args specified (FnCallExprAST)" << std::endl;
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
			std::cerr << "Invalid argument type (FnCallExprAST)" << std::endl;
			return T_ERROR;
		}
	}

	return s->type();
}
