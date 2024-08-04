#ifndef QCINE_COMBOBOX_HPP
#define QCINE_COMBOBOX_HPP

/**
 * QComboBox customizado para o settings bloquear o leaveEvent do WidgetFlutuante.
 */

#include <QComboBox>
#include <QListView>

namespace QCineComboBox {

    class ListView : public QListView {
        Q_OBJECT

    public:
        using QListView::QListView;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void enterBox(bool b);

#pragma clang diagnostic pop

    protected:
        void hideEvent(QHideEvent *event) override {
            Q_EMIT enterBox(false);
            QListView::hideEvent(event);
        }
    };

    class ComboBox : public QComboBox {
        Q_OBJECT

    public:
        explicit ComboBox() {
            view = new ListView();
            connect(view, &ListView::enterBox, this, &ComboBox::enterBox);
            this->setView(view);
        }

    private:
        ListView *view{};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void enterBox(bool b);

#pragma clang diagnostic pop

    protected:
        void mousePressEvent(QMouseEvent *event) override {
            Q_EMIT enterBox(true);
            QComboBox::mousePressEvent(event);
        }
    };

} // QCineComboBox

#endif //QCINE_COMBOBOX_HPP
