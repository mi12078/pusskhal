#ifndef SYMTAB_H
#define SYMTAB_H

#include <map>
#include <stack>
#include "symInfo.hpp"

class SymbolTable 
{
public:
	/*Returns the singleton table*/
	static SymbolTable& get();

	/*Searches the desired scope*/
	SymInfo* searchTable(const std::string& name);

	/*Symbol inserter*/
	/*TODO: we cannot have a variable in a function that bears the same
	 * name as the function itself, it is reserved for the return value
	 * How can we manage that condition?*/
	void insertSymbol(const std::string& name, SymInfo* info);

	/*TODO: Do we need a specific fn for each of the possible values 
	 * of SymInfo* ? */
	void updateSymbol(const std::string& name, SymInfo* info);

	void deleteSymbol(const std::string& name);


	SymbolTable(const SymbolTable& o)
		: _symTab(o._symTab)
	{}
private:
	SymbolTable() {}
	SymbolTable& operator=(SymbolTable& );

	std::map<std::string, std::stack<SymInfo*> > _symTab;
};

#endif
