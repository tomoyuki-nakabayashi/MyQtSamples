/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_SEQUENCER_H_
#define UDP_RECEIVER_SEQUENCER_H_

#include <QObject>
#include <QMetaObject>
#include <QByteArray>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_receiver {
class Sequencer : public QObject {
  Q_OBJECT

 public:
    explicit Sequencer(QObject *parent = Q_NULLPTR);
    const QByteArray& AppendPendingData(const QByteArray &ba);
    void ConstructFrame();

 signals:
    void FrameConstructed(QSharedPointer<Frame> frame);

 private:
    enum class Sequence {RECOVERING = -1, FRAME = 0, SUB_FRAME = 1, UNCHANGED};
    Sequence state_;
    QByteArray pending_data_;
    QSharedPointer<BaseFrameBuilder> builder_;
    QMetaObject::Connection builder_connection_;

 private:
    void ChangeSequence(Sequence next);
    Sequence GetNextState();
    void ConnectToBuilder();

 private slots:
    void onFrameConstructed(QVariant frame);
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_SEQUENCER_H_