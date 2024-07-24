/**
 * O programa vai possuir um background por padrão. Os widgets de controle e playlist
 * irão sobrepor o plano de fundo que poderá ser trocado pela capa do arquivo multimídia
 * ou por um visualizador de vídeos.
 */

#include "Background.hpp"

namespace QCineBackground {

#define coverSize 320

    Background::Background() {
        this->setMouseTracking(true);

        /** Background e logo */
        backgroundTransition = new QCineBackgroundTransition::BackgroundTransition();
        logo = new QCineBackgroundTransition::BackgroundTransition(true, QSize(coverSize, coverSize), defIcon);

        /** Layout principal */
        auto layout = new QGridLayout(this);
        layout->setContentsMargins(QMargins());
        layout->addWidget(backgroundTransition, 0, 0);
        layout->addWidget(logo, 0, 0);
    }

} // QCineBackground