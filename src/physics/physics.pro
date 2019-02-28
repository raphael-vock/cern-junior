TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH = ../vector3d
LIBS += -L../vector3d -lvector3d
PRE_TARGETEDEPS += ../vector3d/libvector3d.a

SOURCES = particle.cpp

HEADERS += \
	particle.h \
	../vector3d/vector3d.h
