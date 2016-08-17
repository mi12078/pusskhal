#ifndef _TYPEAST_HPP_
#define _TYPEAST_HPP_ 1

#include <string>

enum Type { T_INTEGER, T_REAL, T_STRNG, T_ARRAY };

class TypeAST{
public:
  virtual void codegen() const = 0;
  virtual ~TypeAST(){}
};

class BasicType: public TypeAST
{
	BasicType(Type t) :_type(t)
	{}
private:
	Type _type;
};

class IntegerType: public TypeAST{
public:
    IntegerType(int value)
    :_value(value)
    {}
    void codegen() const;
    ~IntegerType(){}

private:
    Type _type;
};

class FloatType: public TypeAST{
public:
    FloatType(float value)
    :_value(value)
    {}
    void codegen() const;
    ~FloatType(){}

private:
    float _value;
};

class CharType: public TypeAST{
public:
    CharType(char value)
    :_value(value)
    {}
    void codegen() const;
    ~CharType(){}
private:
    char _value;
};

class BoolType: public TypeAST{
public:
    BoolType(bool value)
    :_value(value)
    {}
    void codegen() const;
    ~BoolType(){}
private:
    bool _value;
};

class StringType: public TypeAST{
public:
    StringType(string value)
    :_value(value)
    {}
    void codegen() const;
    ~StringType(){}
private:
    string _value;
    
};
/*
//treba dodati ArrayType
class ArrayType: public TypeAST{
public:
    ArrayType
    
private:
    
    
};*/
#endif
