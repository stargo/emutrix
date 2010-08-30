# -------------------------------------------------
# Project created by QtCreator 2010-08-26T22:20:23
# -------------------------------------------------
TARGET = emutrix
VERSION = 0.1
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mainwindow_slots.cpp
HEADERS += sanealsa.h \
    mainwindow.h
FORMS += mainwindow.ui
RESOURCES += emutrix.qrc
LIBS += -lasound
OTHER_FILES += 
DEFINES += APPLICATION_NAME=\\\"$(TARGET)\\\"
