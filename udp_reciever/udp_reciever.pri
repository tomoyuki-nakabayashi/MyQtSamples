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
    $$SRC_DIR/BaseFrameBuilder.cpp \
    $$SRC_DIR/FrameBuilder.cpp \
    $$SRC_DIR/SubFrameBuilder.cpp

HEADERS += \
    $$HEAD_DIR/UdpReciever.h \
    $$SRC_DIR/BaseFrameBuilder.h \
    $$HEAD_DIR/FrameBuilder.h \
    $$HEAD_DIR/SubFrameBuilder.h
