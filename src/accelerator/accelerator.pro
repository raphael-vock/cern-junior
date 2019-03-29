TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH += \
	../color \
	../general \
	../vector3d \
	../physics \

SOURCES += \
	element.cpp \
	accelerator.cpp \

HEADERS += \
	element.h \
	accelerator.h \
