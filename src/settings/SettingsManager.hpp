#ifndef QCINE_SETTINGSMANAGER_HPP
#define QCINE_SETTINGSMANAGER_HPP

#include <QApplication>
#include <QScreen>
#include <QSettings>
#include <QWidget>

#include <Debug.hpp>

#define checkTrue 2
#define checkFalse 0
#define btnIconSize 32
#define playlistMinWidth 300
#define defIcon "appdata/qcine.png"

namespace QCineSettingsManager {

    enum Theme {
        Default = 0,
        Random = 1,
        Gradient = 1,
        Rounded = 2
    };

    enum QCineVideoEngine {
        UseQMediaPlayer = 0,
        UseVlcQT = 1
    };

    class SettingsManager : public QSettings {
        Q_OBJECT

    public:
        explicit SettingsManager(QWidget *window = nullptr);

        QStringList defProgramBackground() { return bgTheme; }

        QStringList defProgramTheme() { return themes; }

        QStringList defProgramEngine() { return engine; }

        QSize minSize() { return {rect.width() / 2, rect.height() / 2}; }

        static QSize res() { return QGuiApplication::primaryScreen()->geometry().size(); }

        void windowMaximize(bool b);

        bool windowMaximize();

        void windowGeometry(QRect rec);

        QRect windowGeometry();

        void splitterSizes(const QList<int> &list);

        QList<int> splitterSizes();

        void programTheme(int i);

        int programTheme();

        void programBackground(int i);

        int programBackground();

        void opacityTheme(int i);

        int opacityTheme();

        void blurBackground(int i);

        int blurBackground();

        void videoEngine(int i);

        int videoEngine();

        void borderSize(int i);

        int borderSize();

        void colorTheme(int i);

        int colorTheme();

        void doubleGradient(int i);

        int doubleGradient();

        void changeEffect(int i);

        int changeEffect();

        void changeEffectBackground(int i);

        int changeEffectBackground();

        void statusEffect(int i);

        int statusEffect();

        void statusEffectBackground(int i);

        int statusEffectBackground();

        void useDefaultBackground(int i);

        int useDefaultBackground();

        void effectHideTime(int i);

        int effectHideTime();

    private:
        QPoint center() { return rect.center() - win->frameGeometry().center(); }

        QRect rect{QGuiApplication::primaryScreen()->geometry()};
        QStringList themes{tr("Default"), tr("Gradient"), tr("Rounded")};
        QStringList bgTheme{tr("Default"), tr("Random")};
        QStringList engine{"QMediaPlayer", "VlcQT"};
        QWidget *win{};
    };

} // QCineSettingsManager

#endif //QCINE_SETTINGSMANAGER_HPP
