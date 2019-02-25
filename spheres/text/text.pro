CONFIG += \
	    c++11\
	    console

CONFIG -= app_bundle

TARGET = console

INCLUDEPATH = ../general

SOURCES += \
	main_text.cpp \
	text_viewer.cpp

HEADERS += \
	../general/content.h \
	text_viewer.h \
	../general/drawable.h \
	../general/canvas.h
