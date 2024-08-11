#ifndef QCINE_COVER_HPP
#define QCINE_COVER_HPP

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

#include <Buttons.hpp>
#include <Style.hpp>

namespace QCineCover {

    class Cover : public QWidget {
        Q_OBJECT

    public:
        explicit Cover(const QPixmap &p);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void playing();

#pragma clang diagnostic pop

    protected:
        void enterEvent(QEnterEvent *event) override;

        void leaveEvent(QEvent *event) override;

    private:
        QCineButtons::Buttons *itemplay{};
        QGridLayout *layout{};
        QLabel *label{};

        QPixmap pxm{};
    };

} // QCineCover

#endif //QCINE_COVER_HPP
