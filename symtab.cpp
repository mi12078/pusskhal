#include "symtab.hpp"

virtual int SymInfo::type()
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

static SymbolTable::SymbolTable& get()
{
	static SymbolTable s;
	return s;
}

/**************************************************************/

SymInfo* SymbolTable::searchTable(const std::string& name)
{
	if(_symTab.find(name) != _symTab.end())
		/*Is this check needed?*/
		if(!_symTab[name].empty())
			return _symTab[name].top();
		else
			return nullptr;
	else
		return nullptr;

}

void SymbolTable::insertSymbol(const std::string& name, SymInfo* info)
{
	_symTab[name].push(info);
}

void SymbolTable::updateSymbol(const std::string& name, SymInfo* info)
{
	SymInfo* s = _symTab.searchTable(name);
	delete s;
	s = info;
}
