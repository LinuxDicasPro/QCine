/**
 * Slider que vai servir como barra de reprodução e barra de volume.
 */

#include "Slider.hpp"

namespace QCineSlider {
    Slider::Slider() {
        this->setOrientation(Qt::Horizontal);
        this->setFocusPolicy(Qt::NoFocus);
        this->setMouseTracking(true);
        this->setTracking(true);
        this->setEnabled(false);
        this->setStyleSheet(QCineStyle::Style().sliderStyle());

        debug = new QCineDebug::Debug();

        connect(this, &Slider::valueChanged, this, &Slider::getValue);
    }

    /**
     * Retorna certinho a posição do clique do mouse.
     * @param pos - Posição de entrada.
     * @return int
     */
    int Slider::pixelPosToRangeValue(int pos) const {
        QStyleOptionSlider opt;
        initStyleOption(&opt);
        QRect gr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
        QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        int sliderMin, sliderMax, sliderLength;

        if (this->orientation() == Qt::Horizontal) {
            sliderLength = sr.width();
            sliderMin = gr.x();
            sliderMax = gr.right() - sliderLength + 1;
        } else {
            sliderLength = sr.height(); /** Suporte a orientação vertical */
            sliderMin = gr.y();
            sliderMax = gr.bottom() - sliderLength + 1;
        }

        return QStyle::sliderValueFromPosition(
                minimum(), maximum(), pos - sliderMin, sliderMax - sliderMin, opt.upsideDown);
    }

    void Slider::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) { /** Botão esquerdo do Mouse */
            QStyleOptionSlider opt;
            initStyleOption(&opt);

            const QRect sliderRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
            const QPoint center = sliderRect.center() - sliderRect.topLeft();

            if (!sliderRect.contains(event->pos())) {
                event->accept();
                QPoint pt = event->pos() - center;
                int value = pixelPosToRangeValue(this->orientation() == Qt::Horizontal ? pt.x() : pt.y());
                setSliderPosition(value);
                triggerAction(SliderMove);
                setRepeatAction(SliderNoAction);
                debug->msg("Tempo de reprodução selecionado", "Slider", {I(value)});
                Q_EMIT sliderMove(value);
            }
        }

        QSlider::mousePressEvent(event);
    }

    void Slider::mouseMoveEvent(QMouseEvent *event) {
        const int o = style()->pixelMetric(QStyle::PM_SliderLength ) - 1;
        int v = QStyle::sliderValueFromPosition(minimum(), maximum(), event->pos().x()-o/2, width()-o, false);
        Q_EMIT onHover((int)event->position().x(), v);
        QSlider::mouseMoveEvent(event);
    }

    void Slider::wheelEvent(QWheelEvent *event) {
        if (event->angleDelta().y() > 0) {
            Q_EMIT sliderMove(val + 5000);
        } else {
            if (val - 5000 < 0)
                Q_EMIT sliderMove(0);
            else
                Q_EMIT sliderMove(val - 5000);
        }
        QAbstractSlider::wheelEvent(event);
    }

} // QCineSlider