#ifndef SYMTAB_H
#define SYMTAB_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include "typeAST.hpp"


/*Base class which contains type information*/
class SymInfo
{
public:
	virtual int type() {
		return _type->type();
	}
	~SymInfo() {
		delete _type;
	}
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
	~ArraySym() {
		for(auto& e: _vec)
			delete e;
	}
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
	~FunSym() {
		delete _retType;
		for(auto& e: _params)
			delete e.second;
	}
	TypeAST* returnValue()
	{
		return _retType;
	}
private:
	TypeAST* _retType;
	std::vector<std::pair<std::string,TypeAST*> > _params;
};


/*****************************************************************************/


class SymbolTable 
{
public:
	/*Table selector*/
	enum TblType { GLOB_TBL, FN_TBL };

	/*Returns the singleton table*/
	static SymbolTable& get()
	{
		static SymbolTable s;
		return s;
	}

	/*Searches the desired scope*/
	SymInfo* searchTable(TblType ty, const std::string& s, const std::string& parent = "")
	{
		if(ty == GLOB_TBL)
			if(_globTable.find(s) != _globTable.end())
				return _globTable[s];
			else
				return nullptr;
		else
			if(_fnTable.find(s) != _fnTable.end())
				if(_fnTable[s].first == parent)
					return _fnTable[s].second;
				else
				{
					std::cerr << "No such symbol in " << parent  << std::endl;
					exit(EXIT_FAILURE);
				}
			else
				return nullptr;
	}

	/*Symbol inserter*/
	void insertSymbol(TblType ty, const std::string& name, 
		SymInfo* info, const std::string& parent = "")
	{
		if(ty == GLOB_TBL)
			if(_globTable.find(name) == _globTable.end())
				_globTable[name] = info;
			else
			{
				std::cerr << "Symbol already exists!" << std::endl;
				exit(EXIT_FAILURE);
			}
		else
			if(_fnTable.find(name) == _fnTable.end())
			{
				if(_globTable.find(parent) != _globTable.end())
					_fnTable[name].first = parent;
				else
				{
					std::cerr << "Nonexistent parent!" << std::endl;
					exit(EXIT_FAILURE);
				}
				_fnTable[name].second = info;
			}
			else
			{
				std::cerr << "Symbol already exists!" << std::endl;
				exit(EXIT_FAILURE);
			}
	}

	/*TODO:to be finished*/
	void updateSymbol(TblType ty, const std::string& name, const std::string &parent ="" )
	{
		if(ty == GLOB_TBL)
			;
		else
			;
	}


	SymbolTable(const SymbolTable& o)
		: _globTable(o._globTable), _fnTable(o._fnTable)
	{}
private:
	SymbolTable() {}
	SymbolTable& operator=(SymbolTable& );

	std::map<std::string, SymInfo*> _globTable;
	/*symbol name, (parent name, info)*/
	std::map<std::string,std::pair<std::string, SymInfo*> >_fnTable;

};

#endif
