CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = particle_test.out

INCLUDEPATH += \
	../../general \
	../../vector3d \
	../../physics \

LIBS += \
	-L../../general -lgeneral \
	-L../../vector3d -lvector3d \
	-L../../physics -lphysics \

PRE_TARGETDEPS +=\
	../../vector3d/libvector3d.a \
	../../physics/libphysics.a \

SOURCES += \
	particle_test.cpp \
