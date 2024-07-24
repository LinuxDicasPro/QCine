#ifndef QCINE_QCINE_HPP
#define QCINE_QCINE_HPP

#include <QCursor>
#include <QGridLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QShortcut>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <Background.hpp>
#include <CheckMouse.hpp>
#include <ClickMapper.hpp>
#include <Controls.hpp>
#include <Debug.hpp>
#include <DefaultPath.hpp>
#include <Effects.hpp>
#include <FloatWidget.hpp>
#include <Icon.hpp>
#include <Player.hpp>
#include <Playlist.hpp>
#include <Settings.hpp>
#include <SettingsManager.hpp>
#include <Style.hpp>

namespace QCine {

    class QCine : public QWidget {
        Q_OBJECT

    public:
        explicit QCine();

        void addArgs(const QStringList &list) { playlist->processFiles(list); };

    protected:
        void changeEvent(QEvent *event) override;

        void enterEvent(QEnterEvent *event) override;

        void closeEvent(QCloseEvent *event) override;

        bool eventFilter(QObject *obj, QEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

        void moveEvent(QMoveEvent *event) override;

    private Q_SLOTS:
        void changeBlur() { background->changeBlur(settingsManager->blurBackground()); };

        void firstPlay(const QString &file = nullptr);

        void play(const QString &file = nullptr);

        void changePlayPause();

        void stop();

        void next();

        void previous();

        void changeEndMedia();

        void changeStack(bool b);

        void changeControls(bool b);

        void changeplaylist(bool b);

        void changeSettings(bool b);

        void changeFileDialog(bool b);

        void statusComboBox(bool b);

        void changeEngine();

        void changeTheme();

        void changeOpacity();

        void changeFullscreen();

        void changeLeave();

        void contextMenu(QPoint point);

    private:
        [[nodiscard]] bool isControlShow() const { return iscontrol; }

        [[nodiscard]] bool isSplit() const { return split; }

        [[nodiscard]] bool isMinimizeMaximized() const { return minimizeMaximized; }

        [[nodiscard]] bool isNoLeave() const { return noLeave; }

        void isNoLeave(bool b) { noLeave = b; }

        void isMinimizeMaximized(bool b) { minimizeMaximized = b; }

        void isSplit(bool b) { split = b; }

        void isControlShow(bool b) { iscontrol = b; }

        QCineBackground::Background *background{};
        QCineCheckMouse::CheckMouse *checkMouse{};
        QCineClickMapper::ClickMapper *clickMapper{};
        QCineControls::Controls *controls{};
        QCineDebug::Debug *debug{};
        QCineEffects::Effects *effects{}, *effectp{};
        QCineFloatWidget::FloatWidget *floatWidget{};
        QCinePlayer::Player *player{};
        QCinePlaylist::Playlist *playlist{};
        QCineSettings::Settings *settings{};
        QCineSettingsManager::SettingsManager *settingsManager{};
        QMenu *menu{};
        QStackedWidget *stackedWidget{};
        QSplitter *splitter{};
        QVBoxLayout *allcontrols{}, *spPlaylist{}, *lsettings{};
        bool split{false}, iscontrol{false}, minimizeMaximized{false}, noLeave{false};
    };

} // QCine

#endif //QCINE_QCINE_HPP
