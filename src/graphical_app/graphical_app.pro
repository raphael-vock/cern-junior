QT += core gui opengl widgets

CONFIG +=\
	c++11\
	console
CONFIG -= app_bundle

TARGET = graphical.out

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
	main_qt_gl.cpp \
	glwidget.cpp \
	glsphere.cpp \
	opengl_view.cpp

HEADERS += \
	glwidget.h \
	vertex_shader.h \
	opengl_view.h \
	glsphere.h \

RESOURCES += \
	resource.qrc
