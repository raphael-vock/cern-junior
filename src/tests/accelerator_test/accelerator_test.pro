CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = accelerator_test.out

INCLUDEPATH += \
	../../accelerator

LIBS += \
	-L../../color -lcolor \
	-L../../vector3d -lvector3d \
	-L../../physics -lphysics \
	-L../../accelerator -laccelerator \

PRE_TARGETDEPS +=\
	../../color/libcolor.a \
	../../vector3d/libvector3d.a \
	../../physics/libphysics.a \
	../../accelerator/libaccelerator.a \

SOURCES += \
	accelerator_test.cpp \
