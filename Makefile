#
# COSC 052 Summer 2019
# Makefile for P4 
#
#

FILE_NAME = main
SUBMIT_NAME = submit
RESULTS_FILE = Results.pdf

a.out: $(FILE_NAME).o Mine.o MineLog.o Exceptions.o DateTime.o
	g++ -std=c++11 $(FILE_NAME).o Mine.o MineLog.o Exceptions.o DateTime.o

$(FILE_NAME).o: $(FILE_NAME).cpp $(FILE_NAME).h LL.h Mine.h MineLog.h Exceptions.h DateTime.h
	g++ -std=c++11 -c $(FILE_NAME).cpp

Mine.o: Mine.cpp Exceptions.h DateTime.h
	g++ -std=c++11 -c Mine.cpp

MineLog.o: MineLog.cpp Mine.h LL.h
	g++ -std=c++11 -c MineLog.cpp

Exceptions.o: Exceptions.cpp Exceptions.h
	g++ -std=c++11 -c Exceptions.cpp

Datetime.o: DateTime.cpp DateTime.h
	g++ -std=c++11 -c DateTime.cpp

.PHONY: submit clean

submit:
	rm -f $(SUBMIT_NAME).zip
	zip $(SUBMIT_NAME).zip Makefile $(FILE_NAME).cpp $(FILE_NAME).h $(RESULTS_FILE) LL.h Mine.cpp Mine.h MineLog.cpp MineLog.h Exceptions.cpp Exceptions.h DateTime.cpp DateTime.h

clean:
	rm -f *.o core a.out
