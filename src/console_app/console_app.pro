CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = console.out

INCLUDEPATH += \
	../vector3d \
	../physics \
	../general

LIBS += \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../general -lgeneral

PRE_TARGETDEPS +=\
	../vector3d/libvector3d.a \
	../physics/libphysics.a \
	../general/libgeneral.a

SOURCES += \
	main_text.cpp \
	text_viewer.cpp

HEADERS += \
	text_viewer.h \
