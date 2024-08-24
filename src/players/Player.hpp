#ifndef QCINE_PLAYER_HPP
#define QCINE_PLAYER_HPP

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

#include <QObject>

#include <Debug.hpp>
#include <QMediaPlayerObject.hpp>
#include <SettingsManager.hpp>

#include <screensaver.h>

#ifdef USE_VLC_QT
#include <VlcQtObject.hpp>
#endif

namespace QCinePlayer {

    class Player : public QObject {
    Q_OBJECT

    public:
        explicit Player();

        [[nodiscard]] bool isPlaying() const { return playing; }

        [[nodiscard]] bool isPausing() const { return pausing; }

        bool isMedia() { return !currentFile.isEmpty(); }

        QString currentMedia() { return currentFile; }

        void setCurrentMedia(const QString &str) { currentFile = str; }

        QWidget *widget() { return player->getVideo(); }

        void setMute(bool b) { player->setMute(b); }

        void setVolume(int i) { player->setVolume(i); }

        bool isMuted() { return player->Muted(); }

        int volume() { return player->Volume(); }

        void play(const QString &str = nullptr);

        void pause();

        void stop();

        void changeEngine();

    public Q_SLOTS:
        void setPosition(int i) { player->setSeek(i); }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void checkVideo(bool b);

        void positionChange(qint64 i);

        void durationChange(qint64 i);

        void endMedia();

#pragma clang diagnostic pop

    private:
        void selectEngine();

        void isVideo();

        void isPlaying(bool b) { playing = b; }

        void isPausing(bool b) { pausing = b; }

        void isBlockScreenSaver(bool b) { blockScreenSaver = b; }

        [[nodiscard]] bool isBlockScreenSaver() const { return blockScreenSaver; }

        QCineDebug::Debug *debug{};
        QCineSettingsManager::SettingsManager *settingsManager{};
        QCineMediaPlayerObject::QMediaPlayerObject *mediaPlayer{};
        QCineMediaPlayerInterface::MediaPlayerInterface *player{};
        ScreenSaver *screenSaver{};

#ifdef USE_VLC_QT
        QCineVlcQtObject::VlcQtObject *vlcPlayer{};
#endif

        QString currentFile{};
        bool playing{false}, pausing{false}, blockScreenSaver{false};
    };

} // QCinePlayer

#endif //QCINE_PLAYER_HPP
