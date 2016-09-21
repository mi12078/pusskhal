#ifndef _TYPEAST_HPP_
#define _TYPEAST_HPP_ 1
#include <vector>
#include <string>

/*TODO: check if we really need copy ctors here*/

const std::string reg[] = { "", "eax", "ebx", "ecx", "edx" };
const int regNo = 4;
enum Register { NONE, R1, R2, R3, R4 };
enum Type { T_INTEGER = 1, T_REAL, T_CHARACTER,
			T_BOOLEAN, T_STRING, T_ERROR, T_VOID, T_ARRAY };

class TypeAST {
public:
  virtual int type() const = 0;
  virtual TypeAST* clone() = 0;
  virtual ~TypeAST(){}
};


class IntegerType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class RealType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class CharacterType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class BooleanType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class StringType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class FunctionType: public TypeAST {
public:
	FunctionType(TypeAST* t, std::vector<std::pair<std::string, TypeAST*> > v)
		: _retType(t), _params(v) {}
	TypeAST* clone();
    int type() const;
	std::vector<std::pair<std::string,TypeAST*> > params() const;
	~FunctionType()
	{
		delete _retType;
		for(auto e : _params)
			delete e.second;
	}
private:
	TypeAST* _retType;
	std::vector<std::pair<std::string,TypeAST*> > _params;
};

class ErrorType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class VoidType: public TypeAST {
public:
	TypeAST* clone();
    int type() const;
};

class ArrayType: public TypeAST {
public:
	TypeAST* clone();
	ArrayType(TypeAST *t) : _elem(t) {}
    int type() const;
	~ArrayType() {
		delete _elem;
	}
private:
	TypeAST* _elem;
};
#endif
