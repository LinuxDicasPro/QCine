/**
 * Classe para sepaarar os botões em um widget separado.
 */

#include "Controls.hpp"

namespace QCineControls {

#define controlFixedHeight 72
#define btnPlaySize 48

    Controls::Controls(QCinePlayer::Player *pPlayer) : player(pPlayer) {
        this->setMouseTracking(true);
        this->setFixedHeight(controlFixedHeight);
        this->setStyleSheet(QCineStyle::Style().widgetStyle(QCineStyle::Controls));

        debug = new QCineDebug::Debug();
        settingsManager = new QCineSettingsManager::SettingsManager();
        slider = new QCineSlider::Slider();
        connect(slider, &QCineSlider::Slider::sliderMove, player, &QCinePlayer::Player::setPosition);

        /** Botões dos controles */
        play = new QCineButtons::Buttons(btnPlaySize, QCineIcon::Play);
        auto stop = new QCineButtons::Buttons(btnIconSize, QCineIcon::Stop);
        auto previous = new QCineButtons::Buttons(btnIconSize, QCineIcon::Previous);
        auto next = new QCineButtons::Buttons(btnIconSize, QCineIcon::Next);
        volume = new QCineButtons::Buttons(btnIconSize, QCineIcon::VolumeUp);
        connect(play, &QPushButton::clicked, this, &Controls::pressPlay);
        connect(stop, &QPushButton::clicked, this, &Controls::pressStop);
        connect(previous, &QPushButton::clicked, this, &Controls::pressPrevious);
        connect(next, &QPushButton::clicked, this, &Controls::pressNext);
        connect(volume, &QPushButton::clicked, this, &Controls::changeMute);

        /** Controle de volume */
        auto volumeslider = new QCineSlider::Slider(); //todo
        volumeslider->setEnabled(true);
        volumeslider->setMinimum(0);
        volumeslider->setMaximum(100);
        volumeslider->setValue(100);
        connect(volumeslider, &QSlider::valueChanged, this, &Controls::changeVolume);
        player->setVolume(volumeslider->value());

        /** Connect do player */
        connect(player, &QCinePlayer::Player::durationChange, this, &Controls::sliderDuration);
        connect(player, &QCinePlayer::Player::positionChange, this, &Controls::sliderPosition);

        /** Layout para o Slider */
        lslider = new QVBoxLayout();
        lslider->setContentsMargins(QCineStyle::Style().spaceSlider());
        lslider->setSpacing(0);
        lslider->addWidget(slider);

        /** Layout dos botões */
        controls = new QHBoxLayout();
        controls->setSpacing(2);
        controls->addSpacing(100); //todo
        controls->addStretch(1);
        controls->addWidget(stop);
        controls->addWidget(previous);
        controls->addWidget(play);
        controls->addWidget(next);
        controls->addWidget(volume);
        controls->addWidget(volumeslider);
        controls->addStretch(1);

        /** Layout principal */
        mainlayout = new QVBoxLayout(this);
        mainlayout->setContentsMargins(0, 0, 0, 2);
        mainlayout->setSpacing(0);
        mainlayout->addStretch(1);
        mainlayout->addLayout(lslider);
        mainlayout->addLayout(controls);
        mainlayout->addStretch(1);
    }

    /**
     * Atualização do tempo de duração do arquivo multimídia.
     * @param i - tempo de duração.
     */
    void Controls::sliderPosition(int i) {
        if (not slider->isSliderDown())
            slider->setValue(i);
    }

    /**
     * Função para setar se o reprodutor está no mudo ou com volume.
     */
    void Controls::changeMute() {
        if (player->isMuted()) {
            player->setMute(false);
            if (player->volume() < 50)
                volume->btn(QCineIcon::VolumeDown);
            else
                volume->btn(QCineIcon::VolumeUp);
        } else {
            player->setMute(true);
            volume->btn(QCineIcon::VolumeOff);
        }
    }

    /**
     * Função para alterar o volume do pragrama.
     */
    void Controls::changeVolume(int i) {
        player->setVolume(i);
        if (i < 50)
            volume->btn(QCineIcon::VolumeDown);
        else
            volume->btn(QCineIcon::VolumeUp);
    }

    void Controls::enterEvent(QEnterEvent *event) {
        debug->msg("Mouse posicionado nos controles", "Controls");
        Q_EMIT noEffect(true);
        QWidget::enterEvent(event);
    }

    void Controls::leaveEvent(QEvent *event) {
        debug->msg("Mouse posicionado fora dos controles", "Controls");
        Q_EMIT noEffect(false);
        QWidget::leaveEvent(event);
    }

    void Controls::paintEvent(QPaintEvent *event) {
        if (settingsManager->doubleGradient() == checkTrue and
            settingsManager->programTheme() == QCineSettingsManager::Gradient) {
            QStyleOption opt;
            opt.initFrom(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }
        QWidget::paintEvent(event);
    }

} // QCineControls