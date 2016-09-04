#include <iostream>
#include "exprAST.hpp"
#include "symTab.hpp"

extern SymbolTable st;

void IntegerExprAST::codegen() const
{
}

void RealExprAST::codegen() const
{
}

void BooleanExprAST::codegen() const
{
}

void StringExprAST::codegen() const
{
}

void VarExprAST::codegen() const
{
}

void ArrExprAST::codegen() const
{
}

void BinaryExprAST::codegen() const
{
}

void UnaryExprAST::codegen() const
{
}

void FnCallExprAST::codegen() const
{
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
		return entry->type();
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
		return T_ERROR;

	return entry->type();
}

int BinaryExprAST::typeCheck() const
{
	int retVal;
	if((retVal = _lhs->typeCheck()) != _rhs->typeCheck())
		return T_ERROR;
	if(_lhs->typeCheck() == T_ERROR || _rhs->typeCheck() == T_ERROR)
		return T_ERROR;
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
