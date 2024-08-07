/**
 * Classe para sepaarar os botões em um widget separado.
 */

#include "Controls.hpp"

namespace QCineControls {

#define controlFixedHeight 72
#define btnPlaySize 48
#define btnPlayMax 2

    Controls::Controls() {
        this->setMouseTracking(true);
        this->setFixedHeight(controlFixedHeight);
        this->setStyleSheet(QCineStyle::Style().widgetStyle(QCineStyle::Controls));

        debug = new QCineDebug::Debug();
        settingsManager = new QCineSettingsManager::SettingsManager();
        slider = new QCineSlider::Slider();
        connect(slider, &QCineSlider::Slider::sliderMove, this, &Controls::valueChanged);

        /** Botões dos controles */
        play = new QCineButtons::Buttons(btnPlaySize, QCineIcon::Play, btnPlayMax);
        auto stop = new QCineButtons::Buttons(btnIconSize, QCineIcon::Stop);
        auto previous = new QCineButtons::Buttons(btnIconSize, QCineIcon::Previous);
        auto next = new QCineButtons::Buttons(btnIconSize, QCineIcon::Next);
        connect(play, &QPushButton::clicked, this, &Controls::pressPlay);
        connect(stop, &QPushButton::clicked, this, &Controls::pressStop);
        connect(previous, &QPushButton::clicked, this, &Controls::pressPrevious);
        connect(next, &QPushButton::clicked, this, &Controls::pressNext);

        /** Layout para o Slider */
        lslider = new QVBoxLayout();
        lslider->setContentsMargins(QCineStyle::Style().spaceSlider());
        lslider->setSpacing(0);
        lslider->addWidget(slider);

        /** Layout dos botões */
        controls = new QHBoxLayout();
        controls->setSpacing(2);
        controls->addStretch(1);
        controls->addWidget(stop);
        controls->addWidget(previous);
        controls->addWidget(play);
        controls->addWidget(next);
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
        if (!slider->isSliderDown())
            slider->setValue(i);
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
        if (settingsManager->doubleGradient() == checkTrue &&
                settingsManager->programTheme() == QCineSettingsManager::Gradient) {
            QStyleOption opt;
            opt.initFrom(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }
        QWidget::paintEvent(event);
    }

} // QCineControls