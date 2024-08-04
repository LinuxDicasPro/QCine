#ifndef QCINE_DIALOGEDITABLE_HPP
#define QCINE_DIALOGEDITABLE_HPP

#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>

namespace QCineDialogEditable {

    class DialogEditable : public QWidget {
        Q_OBJECT

    public:
        explicit DialogEditable();

        QLineEdit *edit() { return lineEdit; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void enterBox();

#pragma clang diagnostic pop

    protected:
        void mousePressEvent(QMouseEvent *event) override;

        void showEvent(QShowEvent *event) override;

    private:
        QHBoxLayout *layout{};
        QLineEdit *lineEdit{};
    };

} // QCineDialogEditable

#endif //QCINE_DIALOGEDITABLE_HPP
