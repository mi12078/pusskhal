#include <iostream>
#include "stmtAST.hpp"
#include "symTab.hpp"

extern SymbolTable st;

void CompoundStmtAST::codegen() const
{
}

void AssignmentStmtAST::codegen() const
{
}

void ArrAssignmentStmtAST::codegen() const
{
}

void IfStmtAST::codegen() const
{
}

void ForStmtAST::codegen() const
{
}

void WhileStmtAST::codegen() const
{
}

void FnDeclStmtAST::codegen() const
{
}

void FnCallStmtAST::codegen() const
{
}

/**************************************************************/

int CompoundStmtAST::typeCheck() const
{
	for(auto e : _v1)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}

int AssignmentStmtAST::typeCheck() const
{
	TypeAST* lhs = st.searchTable(_id);
	int rhs = _rhs->typeCheck();
	if(lhs == nullptr)
	{
		std::cerr << "No symbol named " << _id << std::endl;
		return T_ERROR;
	}
	if(rhs == T_ERROR)
		return T_ERROR;
	if(lhs->type() != rhs)
		return T_ERROR;
	return T_VOID;
}

int ArrAssignmentStmtAST::typeCheck() const
{
	TypeAST* lhs = st.searchTable(_id);
	int index = _index->typeCheck();
	int rhs = _rhs->typeCheck();

	if(lhs == nullptr)
	{
		std::cerr << "No symbol named " << _id << std::endl;
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
		std::cerr << ", symbol already exists" << std::endl;
		return T_ERROR;
	}
	st.insertSymbol(_name, new FunctionType(_retType, _localVars));

	/*placing nullptrs as a scope separator*/
	for(auto e : _localVars)
		st.insertSymbol(e.first, nullptr);

	/*placing the actual symbol info*/
	for(auto e : _localVars)
	{
		if(st.searchTable(e.first))
		{
			/*var with the same name has already been inserted*/
			std::cerr << "Multiple variable declaration in ";
			std::cerr << " function " << _name << std::endl;
			return T_ERROR;
		}
		st.insertSymbol(e.first, e.second);
	}

	retVal = _body->typeCheck() == T_ERROR ? T_ERROR : T_VOID;

	for(auto e : _localVars)
		st.deleteSymbol(e.first);

	return retVal;
}

int FnCallStmtAST::typeCheck() const
{
	TypeAST* s = st.searchTable(_name);
	if(s == nullptr)
	{
		std::cerr << "No symbol named " << s << std::endl;
		return T_ERROR;
	}

	auto params = dynamic_cast<FunctionType*>(s)->params();

	if(params.size() != _args.size())
	{
		std::cerr << "Invalid no. of args specified" << std::endl;
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
			return T_ERROR;
		}
	}

	return s->type();
}
