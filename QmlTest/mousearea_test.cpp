// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlcontext.h>
#include <QtQuick/qquickview.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtGui/qstylehints.h>
#include <QtGui/qtouchdevice.h>
#include "shared/util.h"
#include "shared/visualtestutil.h"

using namespace QQuickVisualTestUtil;

class mousearea_test: public QObject {
  Q_OBJECT

 private slots:
    void FirstTest();
};

void mousearea_test::FirstTest() {
  QVerify(true);
}

QTEST_MAIN(mousearea_test)

#include "mousearea_test.moc"

