/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_SEQUENCER_H_
#define UDP_RECEIVER_SEQUENCER_H_

#include <functional>
#include <QObject>
#include <QMetaObject>
#include <QByteArray>
#include <QSharedPointer>
#include <QScopedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

namespace udp_receiver {
class Sequencer : public QObject {
  Q_OBJECT

 public:
    explicit Sequencer(QObject *parent = Q_NULLPTR);
    const QByteArray& AppendPendingData(const QByteArray &ba);
    bool ConstructFrame();

 signals:
    void FrameConstructed(QSharedPointer<Frame> frame);

 private:
    std::function<void(Sequencer&)> change_state_;
    QByteArray pending_data_;
    QScopedPointer<BaseFrameBuilder> builder_;
    QMetaObject::Connection builder_connection_;

 private:
    void ConnectToBuilder();
    static void ChangeStateOnFrame(Sequencer& self);
    static void ChangeStateOnSubFrame(Sequencer& self);

 private slots:
    void onFrameConstructed(QVariant frame);
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_SEQUENCER_H_