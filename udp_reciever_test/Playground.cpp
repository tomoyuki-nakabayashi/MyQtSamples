/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <functional>
#include <gtest/gtest.h>
#include <QMap>
#include <QVariant>

namespace playground {

class PlayGround : public ::testing::Test {
protected:
  PlayGround()
  {
  }

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(PlayGround, QMapQVariant) {
  QMap<QString, QVariant> map;
  map.insert("int", QVariant(123));

  quint8 v = 255;
  map.insert("uint8", QVariant::fromValue(v));
}

TEST_F(PlayGround, QVariantUnsignedInt8) {
  quint8 v = 255;
  auto byte_v = QVariant::fromValue(v);
  EXPECT_TRUE(byte_v.canConvert<quint8>());

  quint8 retreaved = byte_v.value<quint8>();
  EXPECT_EQ(255, retreaved);
}

QVariant func1(QString str) {
  return QVariant(str.toInt());
}

TEST_F(PlayGround, FunctionMap) {
  QMap<QString, std::function<QVariant (QString)>> map;
  map.insert("int", func1);

  auto variant = map["int"]("15");
  EXPECT_EQ(15, variant.toInt());
}
}  // namespace playground