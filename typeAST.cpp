#include "typeAST.hpp"

int IntegerType::type() const {
	return T_INTEGER;
}
int RealType::type() const {
	return T_REAL;
} 
int CharacterType::type() const {
	return T_CHARACTER;
} 
int BooleanType::type() const {
	return T_BOOLEAN;
} 
int StringType::type() const {
	return T_STRING;
}
int FunctionType::type() const {
	return T_FUNCTION;
}
int ArrayType::type() const {
	return T_ARRAY + _elem->type();
    
}
