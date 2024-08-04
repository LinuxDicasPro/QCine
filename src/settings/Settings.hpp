#ifndef QCINE_SETTINGS_HPP
#define QCINE_SETTINGS_HPP

#include <QCheckBox>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

#include <Buttons.hpp>
#include <Debug.hpp>
#include <ComboBox.hpp>
#include <EnvironmentVariable.hpp>
#include <Style.hpp>
#include <SettingsDefines.hpp>
#include <SettingsManager.hpp>
#include <SettingsSlider.hpp>

namespace QCineSettings {

    class Settings : public QDialog {
        Q_OBJECT

    public:
        explicit Settings();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void dialogShow(bool b);

        void enterBox(bool b);

        void changeTheme();

        void changeBackground();

        void changeOpacity();

        void changeBlur();

        void changeEngine();

        void disableEffect(bool b);

        void disableEffectBG(bool b);

        void changeEffect(int i);

        void changeEffectBG(int i);

        void changeHideEffect(int i);

#pragma clang diagnostic pop

    protected:
        void showEvent(QShowEvent *event) override;

        void hideEvent(QHideEvent *event) override;

        void enterEvent(QEnterEvent *event) override;

    private Q_SLOTS:
        void handleComboBoxChange(int i);

        void handleComboBoxBg(int i);

        void changeOpacityTheme(int i);

        void changeBlurBackground(int i);

        void handleComboBoxEngine(int i);

        void changeBorderTheme(int i);

        void changeColorTheme(bool checked, QRadioButton *button);

        void changeEnableEffect(int i);

        void changeEnableEffectBG(int i);

        void useDefaultBackground(int i);

        void changeEffectDuration(int i);

        void changeEffectDurationBG(int i);

        void changeEffectTime(int i);

    private:
        QGridLayout *controlsEngine{}, *controlsTheme{}, *bgTheme{};
        QGroupBox *enginebox{}, *themebox{}, *bgbox{}, *effcontrol{}, *effectgroup{}, *effectbg{};
        QVBoxLayout *layout{}, *performanceBox{}, *effectBox{}, *customBox{};
        QVBoxLayout *pllayout{}, *bglayout{}, *controllayout{};
        QWidget *performance{}, *effect{}, *custom{};
        QTabWidget *tabWidget{};

        QCheckBox *gradck{}, *effectDisable{}, *effectDisableBG{}, *includedef{};
        QCineDebug::Debug *debug{};
        QCineSettingsManager::SettingsManager *settingsManager{};
        QCineSettingsSlider::SettingsSlider *borderSize{};
    };

} // QCineSettings

#endif //QCINE_SETTINGS_HPP
