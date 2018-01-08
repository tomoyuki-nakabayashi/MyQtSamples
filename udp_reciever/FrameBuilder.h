/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_FRAMEBUILDER_H_
#define UDP_RECIEVER_FRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_reciever {
class FrameBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit FrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{Q_NULLPTR}, finished_(false) {}
    ~FrameBuilder() {}
    QSharedPointer<Frame> GetFrame() override;
    bool Finished() override;
  
 private:
    QSharedPointer<Frame> frame_;
    bool finished_;
  
 private:
    void CreateNewFrame() override;
    FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
    void UpdateFinished() override;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_FRAMEBUILDER_H_
