#ifndef QCINE_CONTROLS_HPP
#define QCINE_CONTROLS_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyleOption>

#include <Buttons.hpp>
#include <Debug.hpp>
#include <SettingsManager.hpp>
#include <Slider.hpp>
#include <Style.hpp>
#include <Player.hpp>

namespace QCineControls {

    class Controls : public QDialog {
        Q_OBJECT

    public:
        explicit Controls(QCinePlayer::Player *pPlayer);

        QCineButtons::Buttons *playBtn() { return play; }

        QVBoxLayout *sliderLayout() { return lslider; }

        void sliderEnabled(bool b) { slider->setEnabled(b); }

    public Q_SLOTS:
        void sliderDuration(int i) { slider->setMaximum(i); }

        void sliderPosition(int i);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void noEffect(bool b);

        void pressPlay();

        void pressStop();

        void pressPrevious();

        void pressNext();

#pragma clang diagnostic pop

    protected:
        void enterEvent(QEnterEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void paintEvent(QPaintEvent* event) override;

    private Q_SLOTS:
        void changeMute();

        void changeVolume(int i);

    private:
        QCineSettingsManager::SettingsManager *settingsManager{};
        QCineButtons::Buttons *play{}, *volume{};
        QCineDebug::Debug *debug{};
        QCinePlayer::Player *player{};
        QCineSlider::Slider *slider{};
        QVBoxLayout *lslider{}, *mainlayout{};
        QHBoxLayout *controls{};
    };

} // QCineControls

#endif //QCINE_CONTROLS_HPP
