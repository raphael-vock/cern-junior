QT += core gui opengl widgets

CONFIG +=\
	c++11\
	console
CONFIG -= app_bundle

TARGET = graphical.out

INCLUDEPATH += \
	../general \
	../physics

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

LIBS += -L../physics -lphysics
PRE_TARGETDEPS += ../physics/libphysics.a

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
	../general/drawable.h \
	../general/canvas.h \
	../general/content.h \
	../physics/particle.h


RESOURCES += \
	resource.qrc
