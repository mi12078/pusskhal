#include "stmtAST.hpp"

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
	SymInfo* lhs = st.searchTable(_id);
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
	SymInfo* lhs = st.searchTable(_id);
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
	/* TODO: check if symbol having the same name as fn already exists,
	 * insert localvars in symtab, remove them at the end of the fn
	 */
	for(auto e : _body)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}

int FnCallStmtAST::typeCheck() const
{
	SymInfo* name = st.searchTable(_name);
	if(name == nullptr)
	{
		std::cerr << "No symbol named " << name << std::endl;
		return T_ERROR;
	}
	for(auto e : _args)
		if(e->typeCheck() == T_ERROR)
			return T_ERROR;
	return T_VOID;
}
