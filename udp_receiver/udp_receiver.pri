QT -= gui
QT += network
CONFIG += console c++11

SRC_DIR = $$PWD
HEAD_DIR = $$PWD
FORM_DIR = $$PWD

INCLUDEPATH *= \
    $$HEAD_DIR

SOURCES += \
    $$SRC_DIR/UdpReceiver.cpp \
    $$SRC_DIR/Sequencer.cpp \
    $$SRC_DIR/BaseFrameBuilder.cpp \
    $$SRC_DIR/FrameBuilder.cpp \
    $$SRC_DIR/SubFrameBuilder.cpp \
    $$SRC_DIR/RecoveryBuilder.cpp

HEADERS += \
    $$HEAD_DIR/UdpReceiver.h \
    $$HEAD_DIR/Sequencer.h \
    $$HEAD_DIR/BaseFrameBuilder.h \
    $$HEAD_DIR/FrameBuilder.h \
    $$HEAD_DIR/SubFrameBuilder.h \
    $$SRC_DIR/RecoveryBuilder.h \
    $$HEAD_DIR/Frame.h
