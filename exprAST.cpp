#include "exprAST.hpp"
#include <iostream>

extern SymbolTable st;
/*will probably need an include or a fwd declaration here...*/

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

void BinaryExprAST::codegen() const
{
}

void UnaryExprAST::codegen() const
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
		std::cerr << "No symbol named " << _id << std::endl;
		return T_ERROR;
	}
}

int ArrExprAST::typeCheck() const
{
	TypeAST* entry = st.searchTable(_id);
	if(entry == nullptr)
	{
		std::cerr << "No symbol named " << _id << std::endl;
		return T_ERROR;
	}
	else if(_index->typeCheck() != T_INTEGER)
		return T_ERROR;

	return entry->type();
}

int BinaryExprAST::typeCheck() const
{
	if(_lhs->typeCheck->type() != _rhs->typeCheck()->type())
		return new T_ERROR;
	if(_lhs->typeCheck->type() == T_ERROR || _rhs->typeCheck()->type() == T_ERROR)
		return new T_ERROR;
	return _lhs->type();
}

int UnaryExprAST::typeCheck() const
{
	return _type->type();
}
