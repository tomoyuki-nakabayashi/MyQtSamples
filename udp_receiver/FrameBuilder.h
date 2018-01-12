/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_FRAMEBUILDER_H_
#define UDP_RECEIVER_FRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_receiver {
class FrameBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit FrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{Q_NULLPTR} {}
    ~FrameBuilder() {}
    QSharedPointer<Frame> GetFrame() override;

 private:
    QSharedPointer<Frame> frame_;
  
 private:
    QSharedPointer<Frame> CreateNewFrame() override;
    FrameBuilderStatus BuildImpl(QDataStream &ds, QSharedPointer<Frame> frame) override;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_FRAMEBUILDER_H_
