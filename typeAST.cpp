#include "typeAST.hpp"

int IntegerType::type() const {
	return T_INTEGER;
}

TypeAST* IntegerType::clone() {
	return new IntegerType;
}

int RealType::type() const {
	return T_REAL;
}

TypeAST* RealType::clone() {
	return new RealType;
}

int CharacterType::type() const {
	return T_CHARACTER;
}

TypeAST* CharacterType::clone() {
	return new CharacterType;
}

int BooleanType::type() const {
	return T_BOOLEAN;
}

TypeAST* BooleanType::clone() {
	return new BooleanType;
}

int StringType::type() const {
	return T_STRING;
}

TypeAST* StringType::clone() {
	return new StringType;
}

int FunctionType::type() const {
	return _ret->type();
}

TypeAST* FunctionType::clone() {
	return new FunctionType(_retType, _params);
}

int ArrayType::type() const {
	return T_ARRAY + _elem->type();
}

TypeAST* ArrayType::clone() {
	return new ArrayType(_elem);
}

int ErrorType::type() const {
	return T_ERROR;
}

TypeAST* ErrorType::clone() {
	return new ErrorType;
}

int VoidType::type() const {
	return T_VOID;
}

TypeAST* VoidType::clone() {
	return new VoidType;
}

