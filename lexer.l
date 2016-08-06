
%{
#include <iostream>
#include <string>
#include "parser.tab.hpp"

/*promeniti strdup, vratiti std::string*/
/*lexer prolazi za primer, za sada*/
/*
sta da vracaju tipovi? zaseban token ili token da se
identifikuju kao tipovi?
*/

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
(?i:begin) { return BEGINT; }
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
(?i:eof) { return EOFT; }

(?i:integer) { return INTEGERTYPE; }
(?i:real) { return REALTYPE; }
(?i:string) { return STRINGTYPE; }
(?i:boolean) { return BOOLEANTYPE; }

(?i:true) { return TRUE; }
(?i:false) { return FALSE; }
[-+]?[0-9]*\.[0-9]+ { yylval.r = atof(yytext); return REAL; }
[-+]?[0-9]+ { yylval.i = atoi(yytext); return INTEGER; }
'([^']+|'')*' { yylval.s = new std::string(yytext); return STRING; }
[_a-zA-Z][_a-zA-Z0-9]* { yylval.id = new std::string(yytext); return ID; }

[ \t\n] { }
[-<>\.+,()=:;\[\]] { return *yytext; }
. {
	std::cerr << "Unknown token " << *yytext << ' ' << std::endl;
	exit(1);
}

%%

