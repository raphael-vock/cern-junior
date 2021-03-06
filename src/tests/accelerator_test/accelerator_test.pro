CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = accelerator_test.out

INCLUDEPATH += \
	../../accelerator \
	../../textview \

LIBS += \
	-L../../color -lcolor \
	-L../../vector3d -lvector3d \
	-L../../physics -lphysics \
	-L../../textview -ltextview \

PRE_TARGETDEPS +=\
	../../color/libcolor.a \
	../../vector3d/libvector3d.a \
	../../physics/libphysics.a \
	../../textview/libtextview.a \

SOURCES += \
	accelerator_test.cpp \
