#ifndef QCINE_SETTINGSSLIDER_HPP
#define QCINE_SETTINGSSLIDER_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

namespace QCineSettingsSlider {

    class SettingsSlider : public QWidget {
        Q_OBJECT

    public:
        explicit SettingsSlider(const QString &tooltip, const QString &unit = nullptr,
                                int tick = 10, int ftick = 0, int size = 0);

        void setValues(int min, int max);

        void setValue(int value);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void valueChanged(int i);

#pragma clang diagnostic pop

    private Q_SLOTS:
        void updateSliderPosition(int i);

    private:
        QSlider *slider{};
        QLabel *labelName{}, *labelValue{}, *l{};
        QHBoxLayout *layout{};
        QVBoxLayout *mainlayout{};
        QWidget *wlayout{};

        int step{0}, fstep{0};
    };

} // QCineSettingsSlider

#endif //QCINE_SETTINGSSLIDER_HPP
