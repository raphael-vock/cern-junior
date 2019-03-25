QT += core gui opengl widgets

CONFIG -= \
	app_bundle \
	console
CONFIG += \
	c++11 \

TARGET = graphical_app

INCLUDEPATH += \
	../vector3d \
	../physics \
	../general

LIBS += \
	-L../general -lgeneral \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../accelerator -laccelerator \

PRE_TARGETDEPS +=\
	../general/libgeneral.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \
	../accelerator/libaccelerator.a \

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
