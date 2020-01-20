all: main.o token.o expressions.o
	g++ main.o  token.o expressions.o -o mycalc
main.o: main.cpp
	g++ -c main.cpp
token.o: token.h token.cpp
	g++ -c token.cpp
expressions.o: expressions.h expressions.cpp
	g++ -c  expressions.cpp
clean:
	rm *.o mycalc

