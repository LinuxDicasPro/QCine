/**
 * QWidget com um QLineEdit que vai abrir para editar a playlist.
 * O atributo QToolTip do widget flutuante é ideal para a interface, mas não abre o QLineEdit.
 * Então, ele foi isolado em outro widget flutuante com outro atributo.
 */

#include "DialogEditable.hpp"

namespace QCineDialogEditable {
    DialogEditable::DialogEditable() {
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setWindowFlag(Qt::Popup, true);

        /** Campo para editar o nome da playlist */
        lineEdit = new QLineEdit();
        lineEdit->setAlignment(Qt::AlignCenter);

        /** Layout associado a janela que abrirá no fullscreen */
        auto layout = new QHBoxLayout(this);
        layout->setContentsMargins(QMargins());
        layout->addWidget(lineEdit);
    }

    void DialogEditable::mousePressEvent(QMouseEvent *event) {
        Q_EMIT enterBox();
        QWidget::mousePressEvent(event);
    }

    void DialogEditable::showEvent(QShowEvent *event) {
        lineEdit->setFocus();
        QWidget::showEvent(event);
    }
} // QCineDialogEditable