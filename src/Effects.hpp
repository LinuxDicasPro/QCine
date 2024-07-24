#ifndef QCINE_EFFECTS_HPP
#define QCINE_EFFECTS_HPP

#include <QGraphicsOpacityEffect>
#include <QObject>
#include <QPropertyAnimation>
#include <QWidget>

#include <SettingsManager.hpp>

namespace QCineEffects {

    class Effects : public QObject {
        Q_OBJECT

    public:
        explicit Effects(QWidget *parent);

        void showEffect(bool b);

        [[nodiscard]] bool isShow() const { return checkshow; }

    public Q_SLOTS:

        void changeEffectDuration(int i) { animation->setDuration(i); }

        void setDisableEffect(bool b) { animation->setDuration(b ? 0 : settingsManager->changeEffect()); }

    private:
        [[nodiscard]] bool isAnimationRunning() const { return animationRunning; }

        void isAnimationRunning(bool b) { animationRunning = b; }

        void isShow(bool b) { checkshow = b; }

        void setCurrent(const QVariant &v) { currentValue = v.toDouble(); }

        QCineSettingsManager::SettingsManager *settingsManager{};
        QGraphicsOpacityEffect *opacityEffect{};
        QPropertyAnimation *animation{};
        QWidget *win{};
        bool animationRunning{false}, checkshow{false};
        double currentValue{0};
    };

} // QCineEffects

#endif //QCINE_EFFECTS_HPP
