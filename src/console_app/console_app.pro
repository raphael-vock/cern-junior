CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = console.out

INCLUDEPATH += \
	../general \
	../accelerator \

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \

PRE_TARGETDEPS +=\
	../color/libcolor.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \

SOURCES += \
	text_viewer.cpp \
	main_text.cpp \

HEADERS += \
	text_viewer.h \
