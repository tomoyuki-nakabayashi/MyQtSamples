include(../udp_receiver/udp_receiver.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
   UdpReceiverTest.cpp  \
   SequencerTest.cpp \
   FrameBuilderInterfaceTest.cpp \
   FrameBuilderTest.cpp \
   SubFrameBuilderTest.cpp \
   PlayGround.cpp

DESTDIR = release
OBJECTS_DIR = ../../tmp/test/.obj
MOC_DIR = ../../tmp/test/.moc
