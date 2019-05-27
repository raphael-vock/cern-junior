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
	accelerator_cli.cpp \

HEADERS += \
	element.h \
	accelerator.h \
	accelerator_cli.h \
