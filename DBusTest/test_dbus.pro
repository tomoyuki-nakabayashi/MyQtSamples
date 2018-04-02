include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib dbus
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    

SOURCES +=     main.cpp \
   play_ground.cpp

DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
