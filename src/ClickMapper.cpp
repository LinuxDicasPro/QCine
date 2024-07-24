/**
 * Mapeador de cliques do mouse para detectar se foi clicado uma vez ou duas vezes.
 */

#include "ClickMapper.hpp"

namespace QCineClickMapper {

#define defClickTime 300

    ClickMapper::ClickMapper(QObject *parent) : QObject(parent) {
        debug = new QCineDebug::Debug();
    }

    /**
     * Iniciando e contabilizando a contagem dos cliques.
     */
    void ClickMapper::mapClicks() {
        if (isBlockClick()) {
            debug->msg("Bloqueando contagem do Mouse", "ClickMapper");
            return;
        }
        m_clickCount++;

        if (m_clickCount == 1) {
            debug->msg("Iniciando a contagem do Mouse", "ClickMapper");
            QTimer::singleShot(defClickTime, this, &ClickMapper::checkClicks);
        }
    }

    /**
     * Verificando se foi dado um clique ou dois cliques.
     */
    void ClickMapper::checkClicks() {
        if (m_clickCount == 1) {
            debug->msg("Um clique no botão do mouse", "ClickMapper");
            Q_EMIT singleClick();
        } else if (m_clickCount == 2) {
            debug->msg("Dois cliques no botão do mouse", "ClickMapper");
            Q_EMIT doubleClick();
        }
        m_clickCount = 0;
    }

} // QCineClickMapper