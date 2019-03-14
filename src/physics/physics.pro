TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH = ../vector3d

SOURCES += \
	particle.cpp \
	universe.cpp \
	box.cpp \
	node.cpp

HEADERS += \
	particle.h \
	universe.h \
	box.h \
	node.h \
	../vector3d.h
