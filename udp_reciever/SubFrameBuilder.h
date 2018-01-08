/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_SUBFRAMEBUILDER_H_
#define UDP_RECIEVER_SUBFRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_reciever {
class SubFrameBuilder : public BaseFrameBuilder
{
  Q_OBJECT
 public:
    explicit SubFrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{nullptr}, finished_(false), count_() {}
    ~SubFrameBuilder() {}
    QSharedPointer<Frame> GetFrame() override;
    bool Finished() override;

 private:
    QSharedPointer<Frame> frame_;
    bool finished_;
    qint32 count_;

 private:
    void CreateNewFrame() override;
    FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
    void UpdateFinished() override;
};
}  // udp_reciever
#endif  // UDP_RECIEVER_SUBFRAMEBUILDER_H_