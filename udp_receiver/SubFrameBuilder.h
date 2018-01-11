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
class SubFrameBuilder : public BaseFrameBuilder
{
  Q_OBJECT
 public:
    explicit SubFrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{nullptr} {}
    ~SubFrameBuilder() {}
    QSharedPointer<Frame> GetFrame() override;

 private:
    QSharedPointer<Frame> frame_;

 private:
    void CreateNewFrame() override;
    FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
};
}  // udp_receiver
#endif  // UDP_RECEIVER_SUBFRAMEBUILDER_H_