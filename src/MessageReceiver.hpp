#ifndef QCINE_MESSAGERECEIVER_HPP
#define QCINE_MESSAGERECEIVER_HPP

#include <QObject>

#include <Debug.hpp>

namespace QCineMessageReceiver {

    class MessageReceiver : public QObject {
        Q_OBJECT

    public Q_SLOTS:
        void receivedMessage(int instanceId, const QByteArray &message);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void args(const QStringList &lst);

#pragma clang diagnostic pop

    };
}

#endif //QCINE_MESSAGERECEIVER_HPP
