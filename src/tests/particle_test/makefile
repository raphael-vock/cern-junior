CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11
VPATH=../../vector3d:../../physics

all: particle_test
vector3d.o: vector3d.cpp vector3d.h
particle.o: vector3d.o particle.cpp particle.h
particle_test.o: particle_test.cpp vector3d.o particle.o
particle_test: particle_test.o vector3d.o particle.o