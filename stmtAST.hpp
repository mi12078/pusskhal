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
    AssignStmtAST(ExprAST *lhs, ExprAST *rhs)
    :_lhs(lhs), _rhs(rhs)
    {}
    void codegen() const;
    ~AssignStmtAST(){
        delete _lhs;
        delete _rhs;
    }
private:
    ExprAST *_lhs,*_rhs;
};

class IfStmtAST: public StmtAST{
public:
    IfStmtAST(ExprAST *con,StmtAST *stmt)
    :_cond(con), _stmt(stmt)
    {}
    void codegen() const;
    ~IfStmtAST(){
        delete _cond;
        delete _stmt;
    }
private:
    ExprAST *_cond;
    StmtAST *_stmt;
};

class ForStmtAST: public StmtAST{
public:
    ForStmtAST()
    :_assign(AssignStmtAST *a), _val(ExprAST *e), _stmt(StmtAST *s)
    {}
    void codegen() const;
    ~ForStmtAST(){
        delete _assign;
        delete _val;
        delete _stmt;
    }
    
private:
    AssignStmtAST *_assign;
    ExprAST *_val;
    StmtAST *_stmt;
};


class WhileStmtAST: public StmtAST{
public:
    WhileStmtAST(ExprAST *cond, StmtAST *stmt)
    :_cond(cond), _stmt(stmt)
    {}
    void codegen() const;
    ~WhileStmtAST(){
        delete _cond;
        delete _stmt;
    }
    
private:
    ExprAST * _cond;
    StmtAST *_stmt;
};

class FnDeclStmtAST : public StmtAST {
public:
private:
};

class FnCallStmtAST : public StmtAST {
public:
private:
};


#endif
