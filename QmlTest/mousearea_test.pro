CONFIG += testcase
TARGET = mousearea_test

SOURCES += mousearea_test.cpp

include (./shared/util.pri)

TESTDATA = data/*

QT += core-private gui-private qml-private quick-private quicktemplates2-private testlib
