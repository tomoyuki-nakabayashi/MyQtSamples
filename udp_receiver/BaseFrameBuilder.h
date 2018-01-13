/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_BASEFRAMEBUILDER_H_
#define UDP_RECEIVER_BASEFRAMEBUILDER_H_

#include <QObject>
#include <QVariant>
#include <QByteArray>
#include <QDataStream>
#include <QSharedPointer>
#include "Frame.h"

namespace udp_receiver {
struct BuilderResult {
  FrameBuilderStatus status;
  qint32 parsed_bytes;

  explicit BuilderResult(FrameBuilderStatus stat = FrameBuilderStatus::NO_ERROR, qint32 len = 0)
    : status{stat}, parsed_bytes{len} {}
};

class BaseFrameBuilder: public QObject {
  Q_OBJECT
 public:
    explicit BaseFrameBuilder(QObject *parent = Q_NULLPTR)
      : QObject(parent), last_result_() {}
    virtual ~BaseFrameBuilder() {}
    BuilderResult Build(QByteArray &ba);

 signals:
    void FrameConstructed(QVariant frame_ptr);

 private:
    virtual QVariant CreateNewFrame() = 0;
    virtual BuilderResult BuildImpl(QByteArray &ds, QVariant frame_ptr) = 0;

 private:
    BuilderResult last_result_;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_BASEFRAMEBUILDER_H_