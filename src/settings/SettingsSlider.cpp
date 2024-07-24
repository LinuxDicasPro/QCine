/**
 * Slider customizado para mostrar os valores definidos para a configuração.
 */

#include "SettingsSlider.hpp"

namespace QCineSettingsSlider {

#define defWidthSlider 255

    SettingsSlider::SettingsSlider(const QString &str, const QString &unit,
                                   int tick, int ftick, int size) : step(tick), fstep(ftick) {

        if (step == 0)
            step++; // interrupted by signal 8:SIGFPE

        if (fstep == 0)
            fstep = step;

        /** Slider */
        slider = new QSlider(Qt::Horizontal);
        slider->setSingleStep(step);
        slider->setPageStep(step);
        slider->setTickInterval(step);
        slider->setTickPosition(QSlider::TicksBothSides);
        connect(slider, &QSlider::valueChanged, this, &SettingsSlider::updateSliderPosition);

        if (size > 0)
            slider->setFixedWidth(size);
        else
            slider->setMinimumWidth(defWidthSlider);

        /** Labels */
        labelName = new QLabel(QString("%1: ").arg(str));
        labelValue = new QLabel(QString::number(slider->value()));

        /** Layout associado a um widget para ajuste da posição */
        auto *wlayout = new QWidget();
        auto *layout = new QHBoxLayout(wlayout);
        layout->setContentsMargins(0, 5, 0, 5);
        layout->addWidget(labelName);
        layout->addWidget(slider);
        layout->addWidget(labelValue);

        if (!unit.isEmpty()) {
            auto l = new QLabel(unit);
            if (size == 0)
                l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            layout->addWidget(l, Qt::AlignLeft);
        }

        /** Layout principal */
        auto mainlayout = new QVBoxLayout(this);
        mainlayout->setContentsMargins(QMargins());
        mainlayout->addWidget(wlayout);
    }

    /**
     * Valores a ser definido no slider customizado.
     * @param min - Valor mínimo.
     * @param max - Valor máximo.
     */
    void SettingsSlider::setValues(int min, int max) {
        slider->setMinimum(min);
        slider->setMaximum(max);
    }

    /**
     * Para setar um valor no slider.
     * @param value - Valor a ser definido.
     */
    void SettingsSlider::setValue(int value) {
        slider->setValue(value);
        labelValue->setText(QString::number(value));
    }

    /**
     * Função para emitir e atualizar os valores atuais do slider.
     * @param i - Valor da posição atual do slider.
     */
    void SettingsSlider::updateSliderPosition(int i) {
        int lstep{step}, v{i};

        if (i == slider->maximum())
            lstep = fstep;

        int offset = i % lstep;

        if (offset != 0)
            v = i - offset;

        slider->setValue(v);
        labelValue->setText(QString::number(v));
        Q_EMIT valueChanged(v);
    }

} // QCineSettingsSlider