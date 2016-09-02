#include "symTab.hpp"

TypeAST* SymbolTable::searchTable(const std::string& name)
{
	if(_symTab.find(name) != _symTab.end())
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

void SymbolTable::insertSymbol(const std::string& name, TypeAST* info)
{
	_symTab[name].push(info);
}

void SymbolTable::deleteSymbol(const std::string& name)
{
	TypeAST* s = SymbolTable::get().searchTable(name);
	/*Is this the correct way to delete?*/
	delete s;
	_symTab[name].pop();
	/* if we only call this fn from a fndeclstmtast fn, there will
	 * always be an underlying nullptr, thus we needn't make the check?
	 */
	if(_symTab[name].top() == nullptr)
		_symTab[name].pop();
}
