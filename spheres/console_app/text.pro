CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = console

INCLUDEPATH += \
	../general \
	../physics

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

LIBS += -L../physics -lphysics
PRE_TARGETDEPS += ../physics/libphysics.a

SOURCES += \
	main_text.cpp \
	text_viewer.cpp

HEADERS += \
	../general/content.h \
	text_viewer.h \
	../general/drawable.h \
	../general/canvas.h
	../physics/particle.h