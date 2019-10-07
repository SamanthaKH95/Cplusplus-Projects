#
# Makefile for P1
#

a.out: main.o DateTime.o DJIA.o History.o
	g++ -std=c++11 main.o DateTime.o DJIA.o History.o

main.o: main.cpp main.h DateTime.h DJIA.h History.h
	g++ -std=c++11 -c main.cpp

DateTime.o: DateTime.cpp DateTime.h
	g++ -std=c++11 -c DateTime.cpp

DJIA.o: DJIA.cpp DJIA.h DateTime.h
	g++ -std=c++11 -c DJIA.cpp

History.o: History.cpp History.h
	g++ -std=c++11 -c History.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp main.h DateTime.cpp DateTime.h DJIA.cpp DJIA.h History.cpp History.h Makefile

clean:
	rm -f *.o core a.out submit.zip
