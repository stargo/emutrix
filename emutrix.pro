# -------------------------------------------------
# Project created by QtCreator 2010-08-26T22:20:23
# -------------------------------------------------
TARGET = emutrix
VERSION = 0.1
TEMPLATE = app
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/mainwindow_slots.cpp
HEADERS += src/sanealsa.h \
    src/mainwindow.h
FORMS += res/mainwindow.ui
RESOURCES += res/emutrix.qrc
LIBS += -lasound
OTHER_FILES += 
DEFINES += APPLICATION_NAME=\\\"$(TARGET)\\\"
