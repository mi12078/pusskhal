#include "stmtAST.hpp"

extern SymbolTable st;

void CompoundStmtAST::codegen() const
{
}

void AssignmentStmtAST::codegen() const
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


int CompoundStmtAST::typeCheck() const
{
	for(auto e : _v1)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}

int AssignmentStmtAST::typeCheck() const
{
	if(st.searchTable(_id) == nullptr)
		return T_ERROR;
	if(_rhs->typeCheck() == T_ERROR)
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
	for(auto e : _body)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}

int FnCallStmtAST::typeCheck() const
{
	for(auto e : _args)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}
