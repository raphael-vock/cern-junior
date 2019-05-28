CONFIG += \
	c++11 \

CONFIG -= app_bundle

TARGET = cern-junior-text

INCLUDEPATH += \
	../general \
	../physics \
	../textview \

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../textview -ltextview

PRE_TARGETDEPS +=\
	../color/libcolor.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \
	../textview/libtextview.a

SOURCES += \
	main_text.cpp
	../textview/textview.cpp

HEADERS += \
	../textview/textview.h
	../textview/acceleratorwidgetconsole.h
