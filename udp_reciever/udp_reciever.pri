QT -= gui
QT += network
CONFIG += console c++11

SRC_DIR = $$PWD
HEAD_DIR = $$PWD
FORM_DIR = $$PWD

INCLUDEPATH *= \
    $$HEAD_DIR

SOURCES += \
    $$SRC_DIR/UdpReciever.cpp \
    $$SRC_DIR/ControlDataBuilder.cpp

HEADERS += \
    $$HEAD_DIR/UdpReciever.h \
    $$HEAD_DIR/ControlDataBuilder.h
