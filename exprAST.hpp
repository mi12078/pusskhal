#ifndef _EXPRAST_HPP 
#define _EXPRAST_HPP 1

#include "typeAST.hpp"

using namespace std;

class ExprAST {
public:
 virtual void codegen() const = 0;    
 virtual ~ExprAST(){}
};

class ConstExprAST: public ExprAST{
public:
    ConstExprAST(TypeAST *val)
    :_val(val)
    {}
    void codegen() const;
    ~ConstExprAST(){
        delete _val;
    }
private:
    TypeAST *_val;
};


class VarExprAST: public ExprAST{
public:
    VarExprAST(TypeAST *val)
    :_val(val)
    {}
    void codegen() const;
    ~VarExprAST(){
        delete _val;
    }
private:
    TypeAST *_val;
};

class BinaryExprAST : public ExprAST{
public:
    BinaryExprAST(char op,ExprAST *ls, ExprAST *rs)
    :_op(op), _ls(ls), _rs(rs)
    {}
    void codegen() const;
    ~BinaryExprAST(){
        delete _ls;
        delete _rs;
    }
private:
    char _op;
    ExprAST *_ls, *_rs;
};

class UnaryExprAST : public ExprAST {
public:
    UnaryExprAST(char op, ExprAST *operand)
    :_operand(operand)
    {}
    void codegen() const;
    ~UnaryExprAST(){
        delete _operand;
    }
private:
    ExprAST *_operand;
};


#endif