CXX=g++
AR=ar

CXXFLAGS=-g -Wall -Weffc++ -Wextra -Wpedantic -g -std=c++11 -O3 -static
ARFLAGS = rcsv

LIBS += -lgmpxx -lgmp

NAME=catalantree

TARGET=libcatalantree.a

OBJECTS=math_tools.o\
        node.o

HEADERS=math_tools.h\
        node.h

PREFIX=/usr/local
LIB_PREFIX=$(PREFIX)/lib/$(NAME)/
INCLUDE_PREFIX=$(PREFIX)/include/$(NAME)/

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

node.o: node.cpp math_tools.h
	$(CXX) $(CXXFLAGS) -c node.cpp

math_tools.o: math_tools.cpp
	$(CXX) $(CXXFLAGS) -c math_tools.cpp

clean:
	rm -rf $(TARGET) *.o

install:
	mkdir -p $(INCLUDE_PREFIX)
	mkdir -p $(LIB_PREFIX)
	cp -rf $(HEADERS) $(INCLUDE_PREFIX)
	cp -rf $(TARGET) $(LIB_PREFIX)
