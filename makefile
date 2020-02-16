# Course: 1633-001
# Instructor: Paul Pospisil
# Assignment: 4.2
# Due Date: March 20th, 2019
#
# This makefile is for the exceutable
# "index".
INDEX=index
MODULES=ignoreList.o indexList.o main.o ioutil.o
CPPFLAGS=-ansi -pedantic-errors -Wall -Wconversion
GCOVFLAGS=-fprofile-arcs -ftest-coverage
GTFLAGS=-lgtest -lgtest_main
TESTING=testIndex
TESTINGMODULES=indexList.cpp indexList.h
GCOVFILE=test

$(INDEX): $(MODULES)
	g++  $(GTFLAGS) $(MODULES) $(GCOVFLAGS) -o $(INDEX)
	gcov indexList.cpp 2> /dev/null | grep -A 1 indexList.cpp

$(TESTING): $(TESTING).o
	g++ $(TESTING).o $(TESTINGMODULES) $(GTFLAGS) $(GCOVFLAGS) -o $(TESTING)

clean:
	/bin/rm -f *~ *.o $(INDEX) *.gcda *.gcov *.gcno

all: clean $(INDEX) $(TESTING)

main.o: indexList.h ignoreList.h ioutil.h globals.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c -g main.cpp

indexList.o: indexList.h globals.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c -g indexList.cpp

ignoreList.o: ignoreList.h globals.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c -g ignoreList.cpp

ioutil.o: ioutil.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c -g ioutil.cpp

$(TESTING).o: globals.h indexList.h
	g++ $(CPPFLAGS) $(GTFLAGS) $(GCOVFLAGS) -c -g $(TESTING).cpp
