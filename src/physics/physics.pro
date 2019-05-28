TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH += \
	../general \
	../vector3d \

SOURCES += \
	particle.cpp \
	box.cpp \
	node.cpp \
	beam.cpp \
	element.cpp \
	accelerator.cpp \
	accelerator_cli.cpp \

HEADERS += \
	particle.h \
	box.h \
	node.h \
	beam.h \
	element.h \
	accelerator.h \
	accelerator_cli.h \
