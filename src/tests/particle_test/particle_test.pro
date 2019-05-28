CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = particle_test.out

INCLUDEPATH += \
	../../physics \

LIBS += \
	-L../../color -lcolor \
	-L../../vector3d -lvector3d \
	-L../../physics -lphysics \

PRE_TARGETDEPS +=\
	../../color/libcolor.a \
	../../vector3d/libvector3d.a \
	../../physics/libphysics.a \

SOURCES += \
	particle_test.cpp \
