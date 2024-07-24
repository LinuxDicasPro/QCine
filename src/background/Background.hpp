#ifndef QCINE_BACKGROUND_HPP
#define QCINE_BACKGROUND_HPP

#include <QGridLayout>
#include <QWidget>

#include <BackgroundTransition.hpp>

namespace QCineBackground {

    class Background : public QWidget {
        Q_OBJECT

    public:
        explicit Background();

    public Q_SLOTS:
        void changeBackground(const QString &str = nullptr) { backgroundTransition->changeBackground(str); }

        void transitionDuration(int i) { backgroundTransition->durationTransition(i); }

        void disableAnimation(bool b) { backgroundTransition->disableAnimation(b); }

        void changeBlur(int i) { backgroundTransition->changeBlur(i); }

    private:
        QCineBackgroundTransition::BackgroundTransition *backgroundTransition{}, *logo{};
    };

} // QCineBackground

#endif //QCINE_BACKGROUND_HPP
