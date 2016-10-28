PROG=prog
CXX=g++
CFLAGS=-g
CXXFLAGS=-std=c++11

$(PROG): parser.tab.o lex.yy.o typeAST.o symTab.o exprAST.o stmtAST.o
	$(CXX) -o $@ $^

stmtAST.o: stmtAST.cpp stmtAST.hpp
	$(CXX) -c $< $(CXXFLAGS) $(CFLAGS)

exprAST.o: exprAST.cpp exprAST.hpp
	$(CXX) -c $< $(CXXFLAGS) $(CFLAGS)

symTab.o: symTab.cpp symTab.hpp
	$(CXX) -c $< $(CXXFLAGS) $(CFLAGS)

typeAST.o: typeAST.cpp typeAST.hpp
	$(CXX) -c $< $(CXXFLAGS) $(CFLAGS)

parser.tab.o: parser.tab.cpp
	$(CXX) -c $< $(CXXFLAGS)
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) -c $< $(CXXFLAGS)
lex.yy.c: lexer.l
	flex $<

.PHONY: clean

clean:
	rm -f lex.yy.* parser.tab.* *.o  *~ *.output $(PROG)
