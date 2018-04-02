/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include <qcoreapplication.h>
#include <qdebug.h>
#include <qvariant.h>

#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QtDBus>
#include "types_interface.h"
#include "global_args.h"

namespace playground {
class PlayGround : public ::testing::Test {
 protected:
    PlayGround() {
    }

    virtual void SetUp() {
      app = new QCoreApplication{g_argc, g_argv};
      adaptor = new TypesInterface(app);
      QDBusConnection::sessionBus().registerObject("/", app);

      iface = new QDBusInterface(QDBusConnection::sessionBus().baseService(), "/",
                                "org.qtproject.Qt.Autotests.TypesInterface",
                                QDBusConnection::sessionBus(),
                                app);
    }

    virtual void TearDown() {
      delete app;
    }

 protected:
    QCoreApplication *app;
    QDBusInterface *iface;
    TypesInterface *adaptor;
};

TEST_F(PlayGround, SimpleTest) {
  QDBusPendingReply<bool> rbool = iface->asyncCall("retrieveBool");
  rbool.waitForFinished();
  EXPECT_TRUE(rbool.isFinished());
  EXPECT_EQ(rbool.argumentAt<0>(), adaptor->retrieveBool());
}
}  // namespace playground