/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_RECOVERYBUILDER_H_
#define UDP_RECEIVER_RECOVERYBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_receiver {
class RecoveryBuilder : public BaseFrameBuilder {
  Q_OBJECT
 public:
    explicit RecoveryBuilder(QObject *parent = Q_NULLPTR)
      : BaseFrameBuilder(parent) {}
    ~RecoveryBuilder() {}
  
 private:
    QVariant CreateNewFrame() override;
    BuilderResult BuildImpl(QByteArray &ba, QVariant frame_ptr) override;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_RECOVERYBUILDER_H_
