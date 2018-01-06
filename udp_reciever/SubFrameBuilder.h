/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_SUBFRAMEBUILDER_H_
#define UDP_RECIEVER_SUBFRAMEBUILDER_H_

#include <memory>
#include <QObject>
#include <QDataStream>
#include "Frame.h"

namespace udp_reciever {
class SubFrameBuilder : public QObject
{
  Q_OBJECT

 public:
    SubFrameBuilder(): status_{FrameBuilderStatus::NO_ERROR}, frame_{nullptr} {}
    FrameBuilderStatus Build(QDataStream &ds, qint32 remaining_data);
    std::shared_ptr<Frame> GetFrame();

 private:
    FrameBuilderStatus status_;
    std::shared_ptr<Frame> frame_;

 private:
    void CreateNewFrame();
    void BuildHeader(QDataStream &ds, qint32 &remaining_data);
    void BuildPayload(QDataStream &ds, qint32 &remaining_data);
    void BuildFooter(QDataStream &ds, qint32 &remaining_data);
};
}  // udp_reciever
#endif  // UDP_RECIEVER_SUBFRAMEBUILDER_H_