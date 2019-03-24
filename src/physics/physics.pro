TEMPLATE = lib

CONFIG = staticlib c++11

INCLUDEPATH += \
	../general \
	../vector3d \

SOURCES += \
	particle.cpp \
	box.cpp \
	node.cpp

HEADERS += \
	particle.h \
	box.h \
	node.h \
