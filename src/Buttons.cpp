/**
 * Classe para definir os botões personalizados para o programa
 * conforme o tema padrão do sistema.
 */

#include "Buttons.hpp"

namespace QCineButtons {

    Buttons::Buttons(int size, QCineIcon::Icons icoName, int max) :
            butonicon(icoName), num(size), maxsize(max) {

        debug = new QCineDebug::Debug();
        icon = new QCineIcon::Icon(size, max);

        /** Estilização padrão dos botões */
        this->setFocusPolicy(Qt::NoFocus);
        this->setStyleSheet("QPushButton {"
                            "    border: none;"
                            "    background-color: transparent;"
                            "}");

        this->setIconSize(QSize(num, num));
        this->setFixedSize(num, num);
        this->setMouseTracking(true);
        this->setIcon(icon->setIcon(icoName));
    }

    /**
     * Aumentar o tamanho dos ícones.
     * @param event - Evento do QT.
     */
    void Buttons::enterEvent(QEnterEvent *event) {
        if (newcolor.isValid())
            this->setIcon(icon->setIcon(butonicon, newcolor));

        setIconSize(QSize(num + maxsize, num + maxsize));
        QPushButton::enterEvent(event);
    }

    void Buttons::leaveEvent(QEvent *event) {
        if (newcolor.isValid())
            this->setIcon(icon->setIcon(butonicon));

        setIconSize(QSize(num, num));
        QPushButton::leaveEvent(event);
    }

    void Buttons::mousePressEvent(QMouseEvent *event) {
        setIconSize(QSize(num - 2, num - 2));
        QPushButton::mousePressEvent(event);
    }

    void Buttons::mouseReleaseEvent(QMouseEvent *event) {
        setIconSize(QSize(num + maxsize, num + maxsize));
        QPushButton::mouseReleaseEvent(event);
    }

} // QCineButtons