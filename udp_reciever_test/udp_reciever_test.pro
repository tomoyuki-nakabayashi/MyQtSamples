include(../udp_reciever/udp_reciever.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
   UdpRecieverTest.cpp  \
   FrameBuilderTest.cpp \
   SubFrameBuilderTest.cpp

DESTDIR = release
OBJECTS_DIR = release/.obj
MOC_DIR = release/.moc