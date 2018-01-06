/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_SUBFRAMEBUILDER_H_
#define UDP_RECIEVER_SUBFRAMEBUILDER_H_

#include <memory>
#include <QObject>
#include <QDataStream>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_reciever {
class SubFrameBuilder : public BaseFrameBuilder
{
  Q_OBJECT
 public:
    explicit SubFrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{nullptr} {}
    ~SubFrameBuilder() {}
    std::shared_ptr<Frame> GetFrame() override;

 private:
    std::shared_ptr<Frame> frame_;

 private:
    void CreateNewFrame() override;
    FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
};
}  // udp_reciever
#endif  // UDP_RECIEVER_SUBFRAMEBUILDER_H_