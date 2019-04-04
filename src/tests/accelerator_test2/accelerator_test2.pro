CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = accelerator_test2.out

INCLUDEPATH += \
	../../accelerator \
	../../textview \

LIBS += \
	-L../../color -lcolor \
	-L../../vector3d -lvector3d \
	-L../../physics -lphysics \
	-L../../accelerator -laccelerator \
	-L../../textview -ltextview \

PRE_TARGETDEPS +=\
	../../color/libcolor.a \
	../../vector3d/libvector3d.a \
	../../physics/libphysics.a \
	../../accelerator/libaccelerator.a \
	../../textview/libtextview.a \

SOURCES += \
	accelerator_test2.cpp \
