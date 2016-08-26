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


TypeAST* IntegerExprAST::typeCheck() const
{
	return _type->type();
}

TypeAST* RealExprAST::typeCheck() const
{
	return _type->type();
}

TypeAST* BooleanExprAST::typeCheck() const
{
	return _type->type();
}

TypeAST* StringExprAST::typeCheck() const
{
	return _type->type();
}

TypeAST* VarExprAST::typeCheck() const
{
	return _type->type();
}

TypeAST* BinaryExprAST::typeCheck() const
{
	if(_lhs->typeCheck->type() != _rhs->typeCheck()->type())
		return new ErrorType;
	return new VoidType;
}

TypeAST* UnaryExprAST::typeCheck() const
{
}
