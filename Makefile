PROG=prog
CXXFLAGS=-std=c++11

$(PROG): parser.tab.o lex.yy.o typeAST.o symTab.o exprAST.o stmtAST.o
	g++ -o $@ $^

stmtAST.o: stmtAST.cpp stmtAST.hpp
	g++ -c $< $(CXXFLAGS)

exprAST.o: exprAST.cpp exprAST.hpp
	g++ -c $< $(CXXFLAGS)

symTab.o: symTab.cpp symTab.hpp
	g++ -c $< $(CXXFLAGS)

typeAST.o: typeAST.cpp typeAST.hpp
	g++ -c $< $(CXXFLAGS)

parser.tab.o: parser.tab.cpp
	g++ -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -c $<
lex.yy.c: lexer.l
	flex $<

.PHONY: clean

clean:
	rm -f lex.yy.* parser.tab.* *.o  *~ *.output $(PROG)
