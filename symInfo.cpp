#include "symInfo.hpp"

int SymInfo::type()
{
	return _type->type();
}

SymInfo::~SymInfo()
{
	delete _type;
}

ArraySym::~ArraySym()
{
	for(auto& e: _vec)
		delete e;
}

FunSym::~FunSym()
{
	delete _retType;
	for(auto& e: _params)
		delete e.second;
}

TypeAST* FunSym::returnValue()
{
	return _retType;
}
