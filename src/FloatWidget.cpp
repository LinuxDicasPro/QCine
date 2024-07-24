/**
 * Widget flutuante para os controles e playlist.
 */

#include "FloatWidget.hpp"

namespace QCineFloatWidget {
    FloatWidget::FloatWidget(QWidget *parent) : QWidget(parent) {
        this->setWindowFlag(Qt::ToolTip, true);
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setMouseTracking(true);
    }

    void FloatWidget::mouseMoveEvent(QMouseEvent *event) {
        Q_EMIT mousePos(event->globalPosition().toPoint());
        QWidget::mouseMoveEvent(event);
    }

    void FloatWidget::mouseReleaseEvent(QMouseEvent *event) {
        if (event->button() & Qt::LeftButton)
            Q_EMIT release();

        QWidget::mouseReleaseEvent(event);
    }

    void FloatWidget::leaveEvent(QEvent *event) {
        QTimer::singleShot(10, [&]() { Q_EMIT leave(); });
        QWidget::leaveEvent(event);
    }

    void FloatWidget::contextMenuEvent(QContextMenuEvent *event) {
        Q_EMIT contextMenu(event->globalPos());
        QWidget::contextMenuEvent(event);
    }

} // QCineFloatWidget