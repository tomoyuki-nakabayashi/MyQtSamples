include(../udp_reciever/udp_reciever.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
   UdpRecieverTest.cpp  \
   ControlDataBuilderTest.cpp \
   SubDataBuilderTest.cpp
