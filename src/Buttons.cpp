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

        this->setProperty("id", (int) icoName);
        this->setFocusPolicy(Qt::NoFocus);
        this->setIconSize(QSize(num, num));
        this->setFixedSize(num, num);
        this->setStyleSheet("QPushButton { border: none; background-color: transparent; }");
        this->setIcon(icon->setIcon(icoName));
    }

    /**
     * Função para alterar o ícone do botão.
     * @param ico - Novo ícone.
     */
    void Buttons::btn(QCineIcon::Icons ico) {
        this->setProperty("id", (int) ico);
        this->setIcon(icon->setIcon(ico));
    }

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