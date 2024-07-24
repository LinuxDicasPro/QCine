/**
 * Classe que cuida do mapeamento do mouse e das ações caso o mouse esteja posicionado
 * em determinados widgets, determinando se ele vai ocultar os widgets ou não.
 */

#include "CheckMouse.hpp"

namespace QCineCheckMouse {

#define checkMouseTimer 200

    CheckMouse::CheckMouse() {
        debug = new QCineDebug::Debug();
        changeHideTimer = QCineSettingsManager::SettingsManager().effectHideTime();

        /** Temporizador para checagem */
        mouseTimer = new QTimer();
        connect(mouseTimer, &QTimer::timeout, this, &CheckMouse::checkMouseMovement);
        mouseTimer->start(checkMouseTimer);

        /** Temporizador para emitir o sinal de mouse parado */
        hideTimer = new QTimer();
        hideTimer->setSingleShot(true);
        connect(hideTimer, &QTimer::timeout, this, &CheckMouse::noMovingMouse);
    }

    /**
     * Verificando se o mouse está ou não se movimentando.
     * Ações serão executados para cada estado.
     */
    void CheckMouse::checkMouseMovement() {
        if (currentPos != lastMousePos) {
            currentPos = lastMousePos;
            QApplication::restoreOverrideCursor();

            if (!isMouseMove()) {
                if (hideTimer->isActive())
                    hideTimer->stop(); // Mouse se movendo, então não deve ocultar.

                isMouseMove(true);
                debug->msg("Mouse se movendo", "CheckMouse");

                if (isNoMouseCheck()) {
                    debug->msg("Emissão bloqueada", "CheckMouse");
                } else {
                    if (!isAlready()) { // Evitando várias emissões
                        isAlready(true);
                        Q_EMIT movingMouse(isAlready());
                    }
                }
            }
        } else { // Mouse parou de se mexer
            if (isMouseMove()) {
                isMouseMove(false);

                debug->msg("Mouse parado", "CheckMouse");
                if (isNoMouseCheck()) {
                    debug->msg("Emissão bloqueada", "CheckMouse");
                } else {
                    if (!hideTimer->isActive())
                        hideTimer->start(changeHideTimer);
                }
            }
        }
    }

    /**
     * Função para emitir um sinal em um determinado tempo em que o mouse está parado.
     */
    void CheckMouse::noMovingMouse() {
        if (!isMouseMove() && !isNoMouseCheck()) {

            if (!isContextMenu() && !isDialog())
                QApplication::setOverrideCursor(Qt::BlankCursor);

            debug->msg("Ocultando controles", "CheckMouse");
            isAlready(false);
            Q_EMIT movingMouse(isAlready());
        }
    }

} // QCineCheckMouse