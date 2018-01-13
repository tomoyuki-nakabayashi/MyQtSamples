/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_SUBFRAMEBUILDER_H_
#define UDP_RECEIVER_SUBFRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"

namespace udp_receiver {
class SubFrameBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit SubFrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent) {}
    ~SubFrameBuilder() {}

 private:
    QVariant CreateNewFrame() override;
    BuilderResult BuildImpl(QByteArray &ba, QVariant frame_ptr) override;
};
}  // udp_receiver
#endif  // UDP_RECEIVER_SUBFRAMEBUILDER_H_