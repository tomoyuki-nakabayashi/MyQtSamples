// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQuick/qquickview.h>
#include <QtQuick/private/qquickrectangle_p.h>
#include "shared/util.h"
#include "shared/visualtestutil.h"

using namespace QQuickVisualTestUtil;

class mousearea_test: public QQmlDataTest {
  Q_OBJECT

 private slots:
    void FirstTest();
};

void mousearea_test::FirstTest() {
  QQuickView *view = new QQuickView;
  view->setSource(testFileUrl("mousearea.qml"));

  QQuickRectangle *item1 = findItem<QQuickRectangle>(view->rootObject(), QLatin1String("redSquare"));
  QVERIFY(item1 != 0);
}

QTEST_MAIN(mousearea_test)

#include "mousearea_test.moc"

