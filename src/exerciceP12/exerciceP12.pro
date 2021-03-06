QT += core gui opengl widgets

CONFIG -= \
	app_bundle \

CONFIG += \
	c++11 \

TARGET = cern-junior-graphical

INCLUDEPATH += \
	../general \
	../physics \

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../physics -lphysics \

PRE_TARGETDEPS +=\
	../color/libcolor.a \
	../vector3d/libvector3d.a \
	../physics/libphysics.a \

SOURCES += \
	main_qt_gl.cpp \
	acceleratorwidgetgl.cpp \
	glsphere.cpp \
	opengl_view.cpp

HEADERS += \
	acceleratorwidgetgl.h \
	vertex_shader.h \
	opengl_view.h \
	glsphere.h \

RESOURCES += \
	resource.qrc
