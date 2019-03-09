CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11
VPATH=../vector3d:../physics

all: test_particles
vector3d.o: vector3d.cpp vector3d.h
particle.o: vector3d.o particle.cpp particle.h
test_particles.o: test_particles.cpp vector3d.o particle.o
test_particles: test_particles.o vector3d.o particle.o
