/**
 * Classe para lidar com a capa que será exibida na playlist caso esteja disponível.
 */

#include "Cover.hpp"

namespace QCineCover {

#define iconSize 64
#define imgsize 96

    Cover::Cover(const QPixmap &p) : pxm(p) {
        label = new QLabel();
        label->setAlignment(Qt::AlignCenter);
        label->setFixedSize(imgsize, imgsize);
        label->setStyleSheet(QCineStyle::Style().labelPixmapStyle());
        label->setPixmap(p);

        itemplay = new QCineButtons::Buttons(iconSize, QCineIcon::ItemPlay);
        itemplay->setFixedSize(imgsize, imgsize);
        itemplay->setVisible(false);
        connect(itemplay, &QCineButtons::Buttons::clicked, this, &Cover::playing);

        layout = new QGridLayout(this);
        layout->setContentsMargins(QMargins());
        layout->addWidget(label, 0, 0);
        layout->addWidget(itemplay, 0, 0, Qt::AlignCenter);
    }

    void Cover::enterEvent(QEnterEvent *event) {
        label->setPixmap(QPixmap());
        itemplay->setVisible(true);
        QWidget::enterEvent(event);
    }

    void Cover::leaveEvent(QEvent *event) {
        label->setPixmap(pxm);
        itemplay->setVisible(false);
        QWidget::leaveEvent(event);
    }

} // QCineCover