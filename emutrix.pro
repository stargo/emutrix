# -------------------------------------------------
# Project created by QtCreator 2010-08-26T22:20:23
# -------------------------------------------------
TARGET = emutrix
VERSION = 0.1
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp
HEADERS += mainwindow.h \
    sanealsa.h
FORMS += mainwindow.ui
RESOURCES += emutrix.qrc
LIBS += -lasound
OTHER_FILES += TODO
DEFINES += APPLICATION_NAME=\\\"$(TARGET)\\\"
