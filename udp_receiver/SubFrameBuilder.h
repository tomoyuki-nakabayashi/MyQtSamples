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
#include "Frame.h"

namespace udp_receiver {
class SubFrameBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit SubFrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent) {}
    ~SubFrameBuilder() {}

 private:
    QSharedPointer<Frame> CreateNewFrame() override;
    FrameBuilderStatus BuildImpl(QDataStream &ds, Frame *frame) override;
};
}  // udp_receiver
#endif  // UDP_RECEIVER_SUBFRAMEBUILDER_H_