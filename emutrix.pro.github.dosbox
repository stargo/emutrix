# -------------------------------------------------
# EMUtrix project
# -------------------------------------------------
# Copyright 2010 Camilo Polymeris
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
TARGET = emutrix
VERSION = 0.3
TEMPLATE = app
SOURCES += src/main.cc \
    src/mainwindow.cc \
    src/mainwindow_slots.cc \
    src/soundcard.cc
HEADERS += src/sanealsa.h \
    src/mainwindow.h \
    src/soundcard.h \
    src/matrix_visibility.h
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
