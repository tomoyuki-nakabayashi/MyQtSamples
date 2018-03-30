// Copyright <2018> <Tomoyuki Nakabayashi>
// This software is released under the MIT License, see LICENSE.

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQuick/qquickview.h>
#include <QtQuick/private/qquicktext_p.h>
#include <QtQuick/private/qquickmousearea_p.h>
#include <QtQuick/private/qquickrectangle_p.h>
#include "shared/util.h"
#include "shared/visualtestutil.h"

using namespace QQuickVisualTestUtil;

class mousearea_test: public QQmlDataTest {
  Q_OBJECT

 public:
    mousearea_test() {};

 private slots:
    void MousePressedPoint();
    void RedSquareTextChanged();
};

void mousearea_test::MousePressedPoint() {
  QQuickView *view = new QQuickView;
  view->setSource(testFileUrl("mousearea.qml"));

  QQuickRectangle *rect = findItem<QQuickRectangle>(view->rootObject(), QLatin1String("redSquare"));
  QVERIFY(rect != Q_NULLPTR);

  QQuickMouseArea *mouseRegion = view->rootObject()->findChild<QQuickMouseArea*>("redSquareMouseArea");
  QVERIFY(mouseRegion != Q_NULLPTR);

  view->show();
  view->requestActivate();
  QTest::qWaitForWindowActive(view);

  QCOMPARE(mouseRegion->mouseX(), rect->x()-10);  // minus margin
  QCOMPARE(mouseRegion->mouseY(), rect->y()-10);  // minus margin

  QMouseEvent event(QEvent::MouseButtonPress, QPoint(100+10, 100+10), Qt::LeftButton, Qt::LeftButton, 0);
  QGuiApplication::sendEvent(view, &event);

  QCOMPARE(mouseRegion->mouseX(), 100.0);
  QCOMPARE(mouseRegion->mouseY(), 100.0);
}

void mousearea_test::RedSquareTextChanged() {
  QQuickView *view = new QQuickView;
  view->setSource(testFileUrl("mousearea.qml"));

  QQuickText *text = findItem<QQuickText>(view->rootObject(), QLatin1String("buttonText"));
  QVERIFY(text != Q_NULLPTR);

  QCOMPARE(text->property("text"), QVariant(""));

  QMouseEvent press(QEvent::MouseButtonPress, QPoint(100+10, 100+10), Qt::LeftButton, Qt::LeftButton, 0);
  QGuiApplication::sendEvent(view, &press);
  QMouseEvent release(QEvent::MouseButtonRelease, QPoint(100+10, 100+10), Qt::LeftButton, Qt::LeftButton, 0);
  QGuiApplication::sendEvent(view, &release);

  QCOMPARE(text->property("text"), QVariant("Clicked (wasHeld=false)"));
}

QTEST_MAIN(mousearea_test)

#include "mousearea_test.moc"

