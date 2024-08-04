#ifndef QCINE_QMEDIAPLAYEROBJECT_HPP
#define QCINE_QMEDIAPLAYEROBJECT_HPP

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QVideoFrame>
#include <QVideoSink>

#include <VideoInterface.hpp>
#include <MediaPlayerInterface.hpp>

namespace QCineMediaPlayerObject {

    class QMediaPlayerObject : public QObject, public QCineMediaPlayerInterface::MediaPlayerInterface {
        Q_OBJECT

    public:
        explicit QMediaPlayerObject();

        void setMedia(const QString &str) override;

        void Play() override { player->play(); }

        void Resume() override { player->play(); }

        void Pause() override { player->pause(); }

        void Stop() override { player->stop(); }

        void setSeek(int i) override { player->setPosition((qint64)i); }

        QWidget *getVideo() override { return video; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void positionChange(qint64 i);

        void durationChange(qint64 i);

        void endMedia();

#pragma clang diagnostic pop

    private Q_SLOTS:
        void changeVideo(const QVideoFrame &frame);

        void changeStatus(QMediaPlayer::MediaStatus st);

        void changeDuration(qint64 i) { Q_EMIT durationChange(i); }

        void changePosition(qint64 i) { Q_EMIT positionChange(i); }

    private:
        QAudioOutput *audio{};
        QMediaPlayer *player{};
        QVideoSink *sink{};
        QCineVideoInterface::VideoWidget *video{};
    };

} // QCineMediaPlayerObject

#endif //QCINE_QMEDIAPLAYEROBJECT_HPP
