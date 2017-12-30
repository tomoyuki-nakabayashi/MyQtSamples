include(../udp_reciever/udp_reciever.pri)
include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
    udp_reciever_test.cpp
