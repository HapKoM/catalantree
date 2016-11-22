CXX=g++
CXXFLAGS=-Wall -g -std=c++11 -O3

INCLUDES = -I..

LIBS += -lgmpxx -lgmp -lgtest -lgtest_main

TARGET=example

TESTS = LibControlTest

OBJECTS = MainTest.o\
          MathTest.o\
          NodeTest.o

all: $(TESTS)

clean:
	rm -rf $(TESTS) *.o

MainTest.o: MainTest.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c MainTest.cpp

MathTest.o: MathTest.cpp ../math_tools.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c MathTest.cpp

NodeTest.o: NodeTest.cpp ../math_tools.h ../node.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c NodeTest.cpp

LibControlTest: $(OBJECTS) ../libcatalantree.a
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@