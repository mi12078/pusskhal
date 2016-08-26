#ifndef _STMTAST_HPP
#define _STMTAST_HPP 1

#include <vector>
#include "exprAST.hpp"
#include "symInfo.hpp"

class StmtAST {
public:
    virtual void codegen() const = 0;
    virtual TypeAST* typeCheck() const = 0;
    virtual ~StmtAST(){}
};
class CompoundStmtAST: public StmtAST{
public:
    CompoundStmtAST(std::vector<StmtAST*> v1)
    :_v1(v1)
    {}
    void codegen() const;
    TypeAST* typeCheck() const;
    ~CompoundStmtAST(){
        for(StmtAST* e : _v1)
            delete e;
    }   
private:
    std::vector<StmtAST*> _v1;
};
class AssignmentStmtAST: public StmtAST{
public:
    AssignmentStmtAST(ExprAST *lhs, ExprAST *rhs)
    :_lhs(lhs), _rhs(rhs)
    {}
    void codegen() const;
    TypeAST* typeCheck() const;
    ~AssignmentStmtAST(){
        delete _lhs;
        delete _rhs;
    }
private:
    ExprAST *_lhs,*_rhs;
};

class IfStmtAST: public StmtAST{
public:
    IfStmtAST(ExprAST *con, StmtAST *stmt)
    :_cond(con), _stmt(stmt)
    {}
    void codegen() const;
    TypeAST* typeCheck() const;
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
    ForStmtAST(AssignmentStmtAST *a, ExprAST *e, StmtAST *s)
    :_assign(a), _val(e), _stmt(s)
    {}
    void codegen() const;
    TypeAST* typeCheck() const;
    ~ForStmtAST(){
        delete _assign;
        delete _val;
        delete _stmt;
    }
    
private:
    AssignmentStmtAST *_assign;
    ExprAST *_val;
    StmtAST *_stmt;
};


class WhileStmtAST: public StmtAST{
public:
    WhileStmtAST(ExprAST *cond, StmtAST *stmt)
    :_cond(cond), _stmt(stmt)
    {}
    void codegen() const;
    TypeAST* typeCheck() const;
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
	FnDeclStmtAST(const std::string& n,
		std::vector<std::pair<std::string, TypeAST*> > lv,
		TypeAST* t, StmtAST* b)
		: _name(n), _localVars(lv), _type(t), _body(b) {}
	void codegen() const;
    TypeAST* typeCheck() const;
private:
	std::string _name;
	std::vector<std::pair<std::string, TypeAST*> >_localVars;
	TypeAST* _type;
	StmtAST* _body;
};

class FnCallStmtAST : public StmtAST {
public:
	FnCallStmtAST(std::vector<ExprAST*> a)
		: _args(a) {}
	void codegen() const;
    TypeAST* typeCheck() const;
private:
	std::vector<ExprAST*> _args;
};

/*yet to see if those below are really needed, suspecting the first
 * one will be used when we get to the VAR block*/
class STInsertStmtAST : public StmtAST {
public:
	STInsertStmtAST (const std::string& n, SymInfo* i)
		: _name(n), _info(i) {}
	void codegen() const;
    TypeAST* typeCheck() const;
private:
	std::string _name;
	SymInfo *_info;
};

class STUpdateStmtAST : public StmtAST {
public:
	STUpdateStmtAST(const std::string& n, SymInfo* i)
		: _name(n), _info(i) {}
	void codegen() const;
    TypeAST* typeCheck() const;
private:
	std::string _name;
	SymInfo *_info;
};

class STDeleteStmtAST : public StmtAST {
public:
	STDeleteStmtAST(const std::string& n)
		: _name(n) {}
	void codegen() const;
    TypeAST* typeCheck() const;
private:
	std::string _name;
};

#endif
