/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_FRAMEBUILDER_H_
#define UDP_RECIEVER_FRAMEBUILDER_H_

#include <memory>
#include <QObject>
#include <QDataStream>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_reciever {
class FrameBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit FrameBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent), frame_{nullptr} {}
    ~FrameBuilder() {}
    std::shared_ptr<Frame> GetFrame() override;
  
 private:
    std::shared_ptr<Frame> frame_;
  
 private:
    void CreateNewFrame() override;
    void BuildHeader(QDataStream &ds, qint32 &remaining_data) override;
    void BuildPayload(QDataStream &ds, qint32 &remaining_data) override;
    void BuildFooter(QDataStream &ds, qint32 &remaining_data) override;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_FRAMEBUILDER_H_
