#ifndef _TYPEAST_HPP_
#define _TYPEAST_HPP_ 1


enum Type { T_INTEGER = 1, T_REAL, T_CHARACTER,
			T_BOOLEAN, T_STRING, T_FUNCTION, T_ARRAY };

class TypeAST{
public:
  virtual int type() const = 0;
  virtual ~TypeAST(){}
};


class IntegerType: public TypeAST{
public:
    int type() const;
};

class RealType: public TypeAST{
public:
    int type() const;
};

class CharacterType: public TypeAST{
public:
    int type() const;
};

class BooleanType: public TypeAST{
public:
    int type() const;
};

class StringType: public TypeAST{
public:
    int type() const;
};

class FunctionType: public TypeAST{
public:
    int type() const;
};

class ArrayType: public TypeAST{
public:
	ArrayType(TypeAST *t) : _elem(t) {}
    int type() const;
	~ArrayType() {
		delete _elem;
	}
private:
	TypeAST* _elem;
};
#endif