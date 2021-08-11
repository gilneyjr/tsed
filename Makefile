CC := g++
SRCDIR := src
BUILDDIR := build

#CFLAGS := -g -std=c++11 -Wno-write-strings
CFLAGS := -std=c++11 
LIB := -ll
INC := -I include

LEXOUT := build/lex.yy.c


syntactic: src/*
	mkdir -p build bin
	lex -t src/tsed.l > build/lex.yy.c
	yacc -d -o build/y.tab.c src/tsed.y
	g++ $(CFLAGS) build/y.tab.c src/node_machine.cpp -I include -o bin/tsed
#	./bin/tsed "[]>[np]&>[]>(#>(#>#>#>#))"
#	./bin/tsed "[] > /()/{123:/NP|PPP/} & > {} > {123:} > [123:] > {...} > [...] > {1:...} > [1:...]"

clean:
	@echo " Cleaning...";
	-@ rm -r build bin/tsed src/*~ src/*.h.gch *~  2>/dev/null || true

.PHONY: clean
