include(../udp_reciever/udp_reciever.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
   UdpRecieverTest.cpp  \
   SequencerTest.cpp \
   FrameBuilderInterfaceTest.cpp \
   FrameBuilderTest.cpp \
   SubFrameBuilderTest.cpp

DESTDIR = release
OBJECTS_DIR = ../../tmp/test/.obj
MOC_DIR = ../../tmp/test/.moc
