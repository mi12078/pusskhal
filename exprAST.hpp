#ifndef _EXPRAST_HPP 
#define _EXPRAST_HPP 1

#include <string>
#include "typeAST.hpp"


class ExprAST {
public:
 	virtual void codegen() const = 0;    
	virtual int typeCheck() const = 0;
};

class IntegerExprAST: public ExprAST {
public:
    IntegerExprAST(int v, TypeAST *t)
    :_val(v), _type(t)
    {}
    void codegen() const;
    int typeCheck() const;
	~IntegerExprAST(){
		delete _type;
	}
private:
    int _val;
	TypeAST *_type; 
};

class RealExprAST: public ExprAST {
public:
    RealExprAST(float v, TypeAST *t)
    :_val(v), _type(t)
    {}
    void codegen() const;
    int typeCheck() const;
	~RealExprAST(){
		delete _type;
	}
private:
    float _val;
	TypeAST *_type; 
};

class BooleanExprAST: public ExprAST {
public:
    BooleanExprAST(bool v, TypeAST *t)
    :_val(v), _type(t)
    {}
    void codegen() const;
    int typeCheck() const;
	~BooleanExprAST(){
		delete _type;
	}
private:
    bool _val;
	TypeAST *_type; 
};

class StringExprAST: public ExprAST {
public:
    StringExprAST(std::string v, TypeAST *t)
    :_val(v), _type(t)
    {}
    void codegen() const;
    int typeCheck() const;
	~StringExprAST(){
		delete _type;
	}
private:
	std::string _val;
	TypeAST *_type; 
};

class VarExprAST: public ExprAST {
public:
    VarExprAST(std::string id)
    :_id(id)
    {}
    void codegen() const;
    int typeCheck() const;
private:
    std::string _id;
};

class ArrExprAST: public ExprAST {
public:
    ArrExprAST(std::string id, ExprAST* i)
    :_id(id), _index(i)
    {}
    void codegen() const;
    int typeCheck() const;
private:
    std::string _id;
	ExprAST* _index;
};

class BinaryExprAST : public ExprAST {
public:
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs)
    :_op(op), _lhs(lhs), _rhs(rhs)
    {}
    void codegen() const;
    int typeCheck() const;
    ~BinaryExprAST(){
        delete _lhs;
        delete _rhs;
    }
private:
    char _op;
    ExprAST *_lhs, *_rhs;
};

class UnaryExprAST : public ExprAST {
public:
    UnaryExprAST(char op, ExprAST *operand)
    :_operand(operand)
    {}
    void codegen() const;
    int typeCheck() const;
    ~UnaryExprAST(){
        delete _operand;
    }
private:
    ExprAST *_operand;
};


#endif
