#include <vector>
#include <map>
#include <string>

/*TODO: write type value getters, etc.*/

enum Type {T_INTEGER, T_ARRAY, T_REAL, T_BOOLEAN, T_FUNCTION};


/*Base class which contains type information*/
class SymInfo
{
private:
	Type _type;
protected:
	SymInfo(Type t) : _type(t) {}
};

/*templated class for representing the basic datatypes in the sym tab;
has a field for its value*/
template<typename T>
class BasicSym : public SymInfo 
{
public:
	BasicSym<T>(Type t, T v)
		: SymInfo(t), _value(v)
		{}
private:
	T _value;
};

/*arrays are problematic, no definite solutions yet*/
/*we provide elements' types, elements themselves*/
class ArraySym : public SymInfo
{
public:
	ArraySym(Type e, std::vector<SymInfo*> v)
		: SymInfo(T_ARRAY), _elemType(e), _vec(v)
		{}
private:
	Type _elemType;
	/*But this excludes arrays being contained in arrays...*/
	/*fuck, what about the template?*/
	std::vector<SymInfo*> _vec;
};

/*we pass parameter types in an vector, as well as fn's return type*/
class FunSym : public SymInfo
{
public:
	FunSym(Type r, std::vector<std::pair<std::string, Type> > v)
		: SymInfo(T_FUNCTION), _retType(r), _params(v)
		{} 
private:
	Type _retType;
	std::vector<std::pair<std::string,Type> > _params;
};

/*Need setter funcs for basic vars, arrays, since they needn't be initialized
when declaring(we will put default values anyway)*/

/*Will most likely need getters as well*/

/*****************************************************************************/


/*
function f(x:integer, y:real): integer;
var a:boolean;
	b: array [0..10] of Integer; //what about the fuckin index ranges!?!
begin end;
*/

/*map of maps; first map key is the scope name, either global or that of
a function, or a global var. Key to second map is a function or a variable;
fn if it is in the global scope, var if it is a func local var or parameter*/
std::map<std::string, std::map<std::string, SymInfo*> > symTab;

int main()
{
	/*vector holding function parameter names(these are not needed?) and types*/
	std::vector<std::pair<std::string,Type> > v;
	v.push_back(std::make_pair("x", T_INTEGER));
	v.push_back(std::make_pair("y", T_REAL));

	/* "" will represent the global namespace */
	/*symTab[scope][symbol]*/
	symTab[""]["f"] = new FunSym(T_INTEGER, v);
	symTab["f"]["x"] = new BasicSym<int>(T_INTEGER, 0);
	symTab["f"]["y"] = new BasicSym<double>(T_REAL, 0.0);
	symTab["f"]["a"] = new BasicSym<bool>(T_BOOLEAN, false);

	/*vector of integers, to be passed to the array constructor*/
	std::vector<SymInfo*> v1;
	for(int i=0;i<10;++i)
		v1.push_back(new BasicSym<int>(T_INTEGER, 0));
	symTab["f"]["b"] = new ArraySym(T_INTEGER, v1);

	/*Is this even right? (array of arrays of integers)*/
	/*or simply avoid this crap?*/
	std::vector<SymInfo*> v2;
	for(int i=0;i<10;++i)
		/*shallow copy?!*/
		v2.push_back(symTab["f"]["b"]);

	symTab["f"]["c"] = new ArraySym(T_ARRAY, v2);

}
/*insertion has proven itself cumbersome for functions and arrays*/

