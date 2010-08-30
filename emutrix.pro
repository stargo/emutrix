# -------------------------------------------------
# Project created by QtCreator 2010-08-26T22:20:23
# -------------------------------------------------
TARGET = emutrix
VERSION = 0.1
TEMPLATE = app
SOURCES += src/main.cc \
    src/mainwindow.cc \
    src/mainwindow_slots.cc
HEADERS += src/sanealsa.h \
    src/mainwindow.h
FORMS += res/mainwindow.ui
RESOURCES += res/emutrix.qrc
LIBS += -lasound
DISTFILES += Makefile \
    README \
    COPYING \
    res/panic.png \
    res/session.png \
    res/link.png \
    res/device.png \
    res/emutrix.png \
    res/mute.png
DEFINES += APPLICATION_NAME=\\\"$(TARGET)\\\"
