#ifndef QCINE_SLIDER_HPP
#define QCINE_SLIDER_HPP

#include <QMouseEvent>
#include <QSlider>
#include <QStyleOption>

#include <Debug.hpp>
#include <Style.hpp>

namespace QCineSlider {

    class Slider : public QSlider {
        Q_OBJECT

    public:
        explicit Slider();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        int sliderMove(int i);

        void onHover(int pos, int value);

#pragma clang diagnostic pop

    protected:
        void mousePressEvent(QMouseEvent *event) override;

        void mouseMoveEvent(QMouseEvent *event) override;

        void wheelEvent(QWheelEvent *event) override;

    private Q_SLOTS:
        void getValue(int value) { val = value; }

    private:
        [[nodiscard]] int pixelPosToRangeValue(int pos) const;

        QCineDebug::Debug *debug{};
        int val{0};
    };

} // QCineSlider

#endif //QCINE_SLIDER_HPP
