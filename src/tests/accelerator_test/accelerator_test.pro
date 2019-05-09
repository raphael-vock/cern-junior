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
	-L../../accelerator -laccelerator \
	-L../../physics -lphysics \
	-L../../textview -ltextview \

PRE_TARGETDEPS +=\
	../../color/libcolor.a \
	../../vector3d/libvector3d.a \
	../../accelerator/libaccelerator.a \
	../../physics/libphysics.a \
	../../textview/libtextview.a \

SOURCES += \
	accelerator_test.cpp \
