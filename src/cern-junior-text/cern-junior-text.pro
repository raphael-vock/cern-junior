CONFIG += \
	c++11 \

CONFIG -= app_bundle

TARGET = cern-junior-text

INCLUDEPATH += \
	../general \
	../accelerator \
	../textview

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../accelerator -laccelerator \
	-L../textview -ltextview

PRE_TARGETDEPS +=\
	../color/libcolor.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \
	../accelerator/libaccelerator.a \
	../textview/libtextview.a

SOURCES += \
	main_text.cpp
	../textview/textview.cpp

HEADERS += \
	../textview/textview.h
	../textview/consolewidget.h
