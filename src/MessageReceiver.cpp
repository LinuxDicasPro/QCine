/**
 * A classe MessageReceiver serve para receber os parâmetros da segunda
 * instância e emitir para ser processado pelo programa na primeira
 * instância, já que a função do SingleApplication é não permitir
 * que o programa use várias instâncias.
 */

#include "MessageReceiver.hpp"

namespace QCineMessageReceiver {

    /**
     * Recebe os argumentos e emite para ser usado
     * como parâmetros para a instância primária.
     * @param instanceId - ID da instância que enviou os argumentos que não será usado nesse projeto.
     * @param message - Os argumentos recebidos.
     */
    void MessageReceiver::receivedMessage(int instanceId, const QByteArray &message) {
        (void) instanceId;

        QCineDebug::Debug().msg("Argumentos recebidos", "MessageReceiver",
                                {QString::fromUtf8(message).replace('\n', ' ')});

        Q_EMIT args(QString::fromUtf8(message).split('\n'));
    }
}
