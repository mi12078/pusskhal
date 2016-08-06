PROG=prog

$(PROG): parser.tab.o lex.yy.o
	g++ -o $@ $^

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
	rm -f lex.yy.* parser.tab.* *~ *.output $(PROG)
