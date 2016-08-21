#ifndef _EXPRAST_HPP 
#define _EXPRAST_HPP 1

#include "typeAST.hpp"


class ExprAST {
public:
	ExprAST(TypeAST *t)
		:_type(t)
	{}
 	virtual void codegen() const = 0;    
	virtual ~ExprAST(){
		delete _type;
	}
private:
	TypeAST *_type; 
};

template<typename T>
class ConstExprAST: public ExprAST{
public:
    ConstExprAST<T>(T v, TypeAST *t)
    :_val(val), ExprAST(t)
    {}
    void codegen() const;
    ~ConstExprAST(){
        delete _val;
    }
private:
    T _val;
};


class VarExprAST: public ExprAST{
public:
    VarExprAST(std::string id, TypeAST *t)
    :_id(id), ExprAST(t)
    {}
    void codegen() const;
    ~VarExprAST(){
        delete _id;
    }
private:
    std::string _id;
};

class BinaryExprAST : public ExprAST{
public:
    BinaryExprAST(char op,ExprAST *lhs, ExprAST *rhs, TypeAST *t)
    :_op(op), _lhs(lhs), _rhs(rhs), ExprAST(t)
    {}
    void codegen() const;
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
    UnaryExprAST(char op, ExprAST *operand, TypeAST *t)
    :_operand(operand), ExprAST(t)
    {}
    void codegen() const;
    ~UnaryExprAST(){
        delete _operand;
    }
private:
    ExprAST *_operand;
};


#endif
