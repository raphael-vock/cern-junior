TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH += \
	../vector3d
	../particle

SOURCES += \
	element.cpp \
	accelerator.cpp \

HEADERS += \
	element.h \
	accelerator.h \
	../particle.h \
	../vector3d.h
