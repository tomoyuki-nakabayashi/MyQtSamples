include(../udp_receiver/udp_receiver.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG -= app_bundle
CONFIG += thread

QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0

LIBS += \
    -lgcov

HEADERS +=    

SOURCES +=     main.cpp \
   UdpReceiverTest.cpp  \
   SequencerTest.cpp \
   FrameBuilderInterfaceTest.cpp \
   FrameBuilderTest.cpp \
   SubFrameBuilderTest.cpp \
   RecoveryBuilderTest.cpp \
   PlayGround.cpp

DESTDIR = release
OBJECTS_DIR = tmp
MOC_DIR = moc
