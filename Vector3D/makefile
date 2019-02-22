CC=$(CXX)
CXXFLAGS = -std=c++11 -pedantic -Wall
CXXFLAGS += -O2
CXXFLAGS += -g
LDLIBS = -lgraph

all: Vector3D_test
Vector3D: Vector_3D.cpp Vector3D.h
Vector3D_test.o: Vector3D_test.cpp Vector3D.h
Vector3D_test: Vector3D_test.o Vector3D.o
	g++ -o Vector3D_test Vector3D_test.o Vector3D.o 
