/**
 * Os efeitos do programa podem ser um pouco sofisticados para não serem separados em uma classe.
 * Isso garantirá melhor controle no ajuste dos efeitos.
 *
 * Refatoração: 2024/07/19
 */

#include "Effects.hpp"

namespace QCineEffects {

    Effects::Effects(QWidget *parent) : win(parent) {
        settingsManager = new QCineSettingsManager::SettingsManager();

        /** Opacidade do Widget. */
        opacityEffect = new QGraphicsOpacityEffect();
        opacityEffect->setOpacity(0);
        win->setGraphicsEffect(opacityEffect);

        /** Animação do widget. */
        animation = new QPropertyAnimation(opacityEffect, "opacity");
        animation->setDuration(
                settingsManager->statusEffect() ? 0 : settingsManager->changeEffect()
        );

        connect(animation, &QPropertyAnimation::valueChanged, this, &Effects::setCurrent);
        connect(animation, &QPropertyAnimation::finished, [&]() { isAnimationRunning(false); });
    }

    /**
     * Função para exibir ou ocultar os controles.
     * @param b - Valor booleano para definir qual efeito vai ser usado.
     */
    void Effects::showEffect(bool b) {
        isShow(b);

        double start{static_cast<double>(b ? 0 : 1)};
        double end{static_cast<double>(b ? 1 : 0)};

        if (isAnimationRunning()) {
            animation->stop();
            animation->setStartValue(currentValue);
        } else {
            animation->setStartValue(start);
        }

        animation->setEndValue(end);
        isAnimationRunning(true);
        animation->start();
    }

} // QCineEffects