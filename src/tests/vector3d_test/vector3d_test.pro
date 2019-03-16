CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = vector3d_test.out

INCLUDEPATH += \
	../../vector3d \

LIBS += \
	-L../../vector3d -lvector3d \

PRE_TARGETDEPS +=\
	../../vector3d/libvector3d.a \

SOURCES += \
	vector3d_test.cpp \

HEADERS += \
	vector3d.h \
