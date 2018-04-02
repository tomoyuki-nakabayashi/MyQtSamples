include(gtest_dependency.pri)

TEMPLATE = app
QT += testlib core dbus
CONFIG -= app_bundle
CONFIG += thread

HEADERS +=    types_interface.h \
              global_args.h

SOURCES +=     main.cpp \
   play_ground.cpp

DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
