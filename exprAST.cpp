#include "exprAST.hpp"
#include <iostream>

void ConstExprAST::codegen() const{
    
    
    std::cout<<"ovo je Konstanta"<<std::endl;
}

void VarExprAST::codegen() const{
    
    
}
void BinaryExprAST::codegen() const{

    
    std::cout<<"ovo je sabiranje"<<std::endl;
}

void UnaryExprAST::codegen() const{
    
    
}
