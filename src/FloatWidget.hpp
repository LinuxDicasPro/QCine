#ifndef QCINE_FLOATWIDGET_HPP
#define QCINE_FLOATWIDGET_HPP

#include <QMouseEvent>
#include <QTimer>
#include <QWidget>

namespace QCineFloatWidget {

    class FloatWidget : public QWidget {
        Q_OBJECT

    public:
        explicit FloatWidget(QWidget *parent);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void mousePos(QPoint point);

        void contextMenu(QPoint point);

        void release();

        void leave();

#pragma clang diagnostic pop

    protected:
        void mouseMoveEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void contextMenuEvent(QContextMenuEvent *event) override;
    };

} // QCineFloatWidget

#endif //QCINE_FLOATWIDGET_HPP
