#ifndef SYMINFO_H
#define SYMINFO_H

#include <vector>
#include <string>
#include "typeAST.hpp"

class StmtAST;

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
	FunSym(TypeAST* r, std::vector<std::pair<std::string, TypeAST*> > v,
		std::vector<StmtAST*> s)
		: SymInfo(new FunctionType), _retType(r), _params(v), _statements(s)
		{} 
	~FunSym();
	TypeAST* returnValue();

private:
	TypeAST* _retType;
	std::vector<std::pair<std::string,TypeAST*> > _params;
	std::vector<StmtAST*> _statements;
};

#endif
