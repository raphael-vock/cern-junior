CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = console.out

INCLUDEPATH += \
	../vector3d \
	../physics \
	../general \

LIBS += \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../general -lgeneral \

PRE_TARGETDEPS +=\
	../general/libgeneral.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \

SOURCES += \
	text_viewer.cpp \
	main_text.cpp \

HEADERS += \
	text_viewer.h \
