TEMPLATE=app
TARGET=tst_qgallery
CONFIG += qmltestcase
CONFIG += console
SOURCES += tst_qgallery.cpp
QUICK_TEST_SOURCE_DIR = ../qgallery/qml

DISTFILES += \
    qml/tst_ImageButton.qml \
    qml/tst_AudioPlayer.qml \
    qml/tst_Controller.qml

RESOURCES += ../qgallery/qml.qrc
