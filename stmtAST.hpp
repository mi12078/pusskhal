#ifndef _STMTAST_HPP
#define _STMTAST_HPP 1

#include "exprAST.hpp"
#include <vector>

class StmtAST {
public:
    virtual void codegen() const = 0;
    virtual ~StmtAST(){}
};
class CompoundStmtAST: public StmtAST{
public:
    CompoundStmtAST(std::vector<StmtAST*> v1)
    :_v1(v1)
    {}
    void codegen() const;
    ~CompoundStmtAST(){
        for(StmtAST* e : _v1)
            delete e;
    }   
private:
    std::vector<StmtAST*> _v1;
};
class AssignStmtAST: public StmtAST{
public:
    AssignStmtAST(ExprAST *ls, ExprAST *rs)
    :_ls(ls), _rs(rs)
    {}
    void codegen() const;
    ~AssignStmtAST(){
        delete _ls;
        delete _rs;
    }
private:
    ExprAST *_ls,*_rs;
};

class IfStmtAST: public StmtAST{
public:
    IfStmtAST(ExprAST *con,CompoundStmtAST *block)
    :_cond(con), _block(block)
    {}
    void codegen() const;
    ~IfStmtAST(){
        delete _cond;
        delete _block;
    }
private:
    ExprAST *_cond;
    CompoundStmtAST *_block;
};

class ForStmtAST: public StmtAST{
public:
    ForStmtAST()
    :_assign(), _val(), _block()
    {}
    void codegen() const;
    ~ForStmtAST(){
        delete _assign;
        delete _val;
        delete _block;
    }
    
private:
    AssignStmtAST *_assign;
    ExprAST *_val;
    CompoundStmtAST *_block;
};


class WhileStmtAST: public StmtAST{
public:
    WhileStmtAST(ExprAST *cond, CompoundStmtAST *block)
    :_cond(cond), _block(block)
    {}
    void codegen() const;
    ~WhileStmtAST(){
        delete _cond;
        delete _block;
    }
    
    
private:
    ExprAST * _cond;
    CompoundStmtAST *_block;
};


#endif