CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11
VPATH=../../vector3d

all: vector3d_test
vector3d.o: vector3d.cpp vector3d.h
vector3d_test.o: vector3d.o vector3d_test.cpp vector3d.h
vector3d_test: vector3d.o vector3d_test.o
