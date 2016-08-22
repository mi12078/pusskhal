#ifndef SYMTAB_H
#define SYMTAB_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include "typeAST.hpp"


/*Base class which contains type information*/
class SymInfo
{
public:
	virtual int type();
	~SymInfo();

protected:
	TypeAST* _type;
	SymInfo(TypeAST* t) : _type(t) {}
};

/*templated class for representing the basic datatypes in the sym tab;
has a field for its value*/
template<typename T>
class BasicSym : public SymInfo 
{
public:
	BasicSym<T>(TypeAST* t, T v)
		: SymInfo(t), _value(v)
		{}
private:
	T _value;
};

/*we provide elements' types, elements themselves*/
class ArraySym : public SymInfo
{
public:
	ArraySym(TypeAST* e, std::vector<SymInfo*> v)
		: SymInfo(new ArrayType(e)), _vec(v)
		{}
	~ArraySym();

private:
	std::vector<SymInfo*> _vec;
};

/*we pass parameter types in an vector, as well as fn's return type*/
class FunSym : public SymInfo
{
public:
	FunSym(TypeAST* r, std::vector<std::pair<std::string, TypeAST*> > v)
		: SymInfo(new FunctionType), _retType(r), _params(v)
		{} 
	~FunSym();
	TypeAST* returnValue();

private:
	TypeAST* _retType;
	std::vector<std::pair<std::string,TypeAST*> > _params;
};


/*****************************************************************************/


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


	SymbolTable(const SymbolTable& o)
		: symTab(o.symTab)
	{}
private:
	SymbolTable() {}
	SymbolTable& operator=(SymbolTable& );

	std::map<std::string, std::stack<SymInfo*> > _symTab;
};

#endif
