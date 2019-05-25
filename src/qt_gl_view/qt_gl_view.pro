QT += core gui opengl widgets

CONFIG -= \
	app_bundle \

CONFIG += \
	c++11 \

TARGET = cern-junior

INCLUDEPATH += \
	../general \
	../accelerator \

LIBS += \
	-L../color -lcolor \
	-L../vector3d -lvector3d \
	-L../accelerator -laccelerator \
	-L../physics -lphysics \

PRE_TARGETDEPS +=\
	../color/libcolor.a \
	../vector3d/libvector3d.a \
	../accelerator/libaccelerator.a \
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
