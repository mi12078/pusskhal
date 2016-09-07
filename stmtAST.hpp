#ifndef _STMTAST_HPP
#define _STMTAST_HPP 1

#include <vector>
#include "exprAST.hpp"

class StmtAST {
public:
    virtual void codegen() const = 0;
    virtual int typeCheck() const = 0;
    virtual ~StmtAST(){}
};

class EmptyStmtAST: public StmtAST{
public:
    void codegen() const;
    int typeCheck() const;
};

class CompoundStmtAST: public StmtAST{
public:
    CompoundStmtAST(std::vector<StmtAST*> v1)
    :_v1(v1)
    {}
    void codegen() const;
    int typeCheck() const;
    ~CompoundStmtAST(){
        for(StmtAST* e : _v1)
            delete e;
    }   
private:
    std::vector<StmtAST*> _v1;
};

class MainBlockStmtAST: public StmtAST {
public:
    MainBlockStmtAST(StmtAST* s)
		: _stmt(s)
    {}
    void codegen() const;
    int typeCheck() const;
private:
	StmtAST* _stmt;
};

class AssignmentStmtAST: public StmtAST{
public:
    AssignmentStmtAST(const std::string& id, ExprAST *rhs)
    :_id(id), _rhs(rhs)
    {}
    void codegen() const;
    int typeCheck() const;
    ~AssignmentStmtAST(){
        delete _rhs;
    }
private:
	std::string _id;
    ExprAST *_rhs;
};

class ArrAssignmentStmtAST: public StmtAST{
public:
    ArrAssignmentStmtAST(const std::string& id, ExprAST* index, ExprAST *rhs)
    :_id(id), _index(index), _rhs(rhs)
    {}
    void codegen() const;
    int typeCheck() const;
    ~ArrAssignmentStmtAST(){
        delete _index;
        delete _rhs;
    }
private:
	std::string _id;
    ExprAST *_index;
    ExprAST *_rhs;
};

class IfStmtAST: public StmtAST{
public:
    IfStmtAST(ExprAST *con, StmtAST *stmt)
    :_cond(con), _stmt(stmt)
    {}
    void codegen() const;
    int typeCheck() const;
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
    ForStmtAST(AssignmentStmtAST *a, ExprAST *e, StmtAST *s, int i)
    :_assign(a), _val(e), _stmt(s), _inc(i)
    {}
    void codegen() const;
    int typeCheck() const;
    ~ForStmtAST(){
        delete _assign;
        delete _val;
        delete _stmt;
    }
    
private:
    AssignmentStmtAST *_assign;
    ExprAST *_val;
    StmtAST *_stmt;
	int _inc;
};


class WhileStmtAST: public StmtAST{
public:
    WhileStmtAST(ExprAST *cond, StmtAST *stmt)
    :_cond(cond), _stmt(stmt)
    {}
    void codegen() const;
    int typeCheck() const;
    ~WhileStmtAST(){
        delete _cond;
        delete _stmt;
    }
    
private:
    ExprAST * _cond;
    StmtAST *_stmt;
};

class VarDeclStmtAST : public StmtAST {
public:
	VarDeclStmtAST(std::vector<std::pair<std::string, TypeAST*> > v)
		: _vars(v) {}
	void codegen() const;
    int typeCheck() const;
	std::vector<std::pair<std::string, TypeAST*> > getVars() const;
private:
	std::vector<std::pair<std::string, TypeAST*> > _vars;
};

class FnDeclStmtAST : public StmtAST {
public:
	FnDeclStmtAST(const std::string& n,
		VarDeclStmtAST* vd,
		TypeAST* t, StmtAST* b)
		: _name(n), _fnVars(vd), _retType(t), _body(b) {}
	void codegen() const;
    int typeCheck() const;
private:
	std::string _name;
	VarDeclStmtAST* _fnVars;
	TypeAST* _retType;
	StmtAST* _body;
};

class FnCallStmtAST : public StmtAST {
public:
	FnCallStmtAST(const std::string& n, std::vector<ExprAST*> a)
		: _name(n), _args(a) {}
	void codegen() const;
    int typeCheck() const;
private:
	std::string _name;
	std::vector<ExprAST*> _args;
};

#endif
