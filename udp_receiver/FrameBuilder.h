/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_FRAMEBUILDER_H_
#define UDP_RECEIVER_FRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include <QVector>
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
    void EmitTestSignal();

 private:
    QSharedPointer<Frame> frame_;
  
 private:
    void CreateNewFrame() override;
    FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_FRAMEBUILDER_H_
