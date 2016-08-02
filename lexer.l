
%{
#include <iostream>

/*promeniti strdup, vratiti std::string*/
/*lexer prolazi za primer, za sada*/

%}

%option noyywrap
%x COMMENT


%%

"(*" 		  BEGIN(COMMENT);
<COMMENT>"*)" BEGIN(INITIAL);
<COMMENT>.    { }
(?i:program) { return PROGRAM; }
(?i:const) { return CONST; }
(?i:type) { return TYPE; }
(?i:var) { return VAR; }
(?i:procedure) { return PROCEDURE; }
(?i:begin) { return BEGIN; }
(?i:end) { return END; }
(?i:while) { return WHILE; }
(?i:not) { return NOT; }
(?i:do) { return DO; }
(?i:if) { return IF; }
(?i:of) { return OF; }
(?i:then) { return THEN; }
(?i:for) { return FOR; }
(?i:to) { return TO; }
(?i:downto) { return DOWNTO; }
(?i:array) { return ARRAY; }
[a-zA-Z]+ { yylval.s = strdup(yytext); return ID; }
[-+]?[0-9]+(\.[0-9]+)? { yylval.n = atoi(yytext); return NUM; }
[ \t\n] { }
[-<>\.+,()=:;\[\]] { return *yytext; }
. {
	std::cerr << "Unknown token " << *yytext << ' ' << std::endl;
	exit(1);
}

%%

/*int main()
{
	return yylex();
}
*/
