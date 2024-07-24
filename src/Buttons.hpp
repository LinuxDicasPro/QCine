#ifndef QCINE_BUTTONS_HPP
#define QCINE_BUTTONS_HPP

#include <QPainter>
#include <QPushButton>

#include <Debug.hpp>
#include <DefaultPath.hpp>
#include <Icon.hpp>

namespace QCineButtons {

#define defMax 2

    class Buttons : public QPushButton {
        Q_OBJECT

    public:
        explicit Buttons(int size, QCineIcon::Icons icon, int max = defMax);

        void btn(QCineIcon::Icons ico) { this->setIcon(icon->setIcon(ico)); }

        void pressColor(const QColor &color) { newcolor = color; }

    protected:
        void enterEvent(QEnterEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        QCineIcon::Icons butonicon{};
        QCineIcon::Icon *icon{};
        QCineDebug::Debug *debug{};
        int maxsize, num;
        QColor newcolor{};
    };

} // QCineButtons

#endif //QCINE_BUTTONS_HPP
