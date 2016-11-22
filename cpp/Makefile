CXX=g++
AR=ar

CXXFLAGS=-g -Wall -Wextra -Wpedantic -g -std=c++11 -O3 -static
ARFLAGS = rcsv

LIBS += -lgmpxx -lgmp

TARGET=libcatalantree.a

OBJECTS=math_tools.o\
        node.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

node.o: node.cpp math_tools.h
	$(CXX) $(CXXFLAGS) -c node.cpp

math_tools.o: math_tools.cpp
	$(CXX) $(CXXFLAGS) -c math_tools.cpp

clean:
	rm -rf $(TARGET) *.o
