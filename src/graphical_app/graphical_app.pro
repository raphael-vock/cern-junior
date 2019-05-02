QT += core gui opengl widgets

CONFIG -= \
	app_bundle \

CONFIG += \
	c++11 \

TARGET = graphical_app

INCLUDEPATH += \
	../general \
	../accelerator \

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \
	-L../accelerator -laccelerator \

PRE_TARGETDEPS +=\
	../color/libcolor.a \
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
