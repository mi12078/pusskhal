#include "symTab.hpp"

/* TODO: see if it is necessary to separate scopes with nullptrs,
 * if so, reimplement insertion/deletion
 */

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

SymbolTable& SymbolTable::get()
{
	static SymbolTable s;
	return s;
}

void SymbolTable::insertSymbol(const std::string& name, SymInfo* info)
{
	_symTab[name].push(info);
}

void SymbolTable::updateSymbol(const std::string& name, SymInfo* info)
{
	SymInfo* s = SymbolTable::get().searchTable(name);
	delete s;
	s = info;
}
void SymbolTable::deleteSymbol(const std::string& name)
{
	SymInfo* s = SymbolTable::get().searchTable(name);
	delete s;
	_symTab[name].pop();
}
