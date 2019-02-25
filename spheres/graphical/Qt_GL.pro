QT += core gui opengl widgets
CONFIG +=\
	c++11\
	console
CONFIG -= app_bundle

TARGET = graphical

INCLUDEPATH = ../general

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
	../general/content.h

RESOURCES += \
	resource.qrc
