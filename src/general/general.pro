TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH += \
	../vector3d \
	../physics \

HEADERS += \
	content.h \
	drawable.h \
	canvas.h \
	../vector3d/vector3d.h \
	../physics/particle.h
