#include "exprAST.hpp"
#include <iostream>

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
	return _type->type();
}

int BinaryExprAST::typeCheck() const
{
	if(_lhs->typeCheck->type() != _rhs->typeCheck()->type())
		return new ErrorType;
	return new VoidType;
}

int UnaryExprAST::typeCheck() const
{
	return _type->type();
}
