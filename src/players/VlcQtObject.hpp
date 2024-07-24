#ifndef QCINE_VLCQTOBJECT_HPP
#define QCINE_VLCQTOBJECT_HPP

#include <QObject>

#include <MediaPlayerInterface.hpp>

#include <core/Common.h>
#include <core/Instance.h>
#include <core/Media.h>
#include <core/MediaPlayer.h>
#include <widgets/WidgetVideo.h>

namespace QCineVlcQtObject {

    class VlcQtObject : public QObject, public QCineMediaPlayerInterface::MediaPlayerInterface {
        Q_OBJECT

    public:
        explicit VlcQtObject();

        void setMedia(const QString &str) override;

        void Play() override { player->play(); }

        void Resume() override { player->resume(); }

        void Pause() override { player->pause(); }

        void Stop() override { player->stop(); }

        void setSeek(int i) override { player->setTime(i); }

//            auto t = player->time();
//            player->stop();
//            args = {"--video-filter=transform", "--transform-type=180"};
//            initPlayer();
//            player->openOnly(new VlcMedia(media, true, instance));
//            player->play();
//            player->setTime(t);

        VlcWidgetVideo *getVideo() { return video; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void positionChange(qint64 i);

        void durationChange(qint64 i);

        void endMedia();

#pragma clang diagnostic pop

    private Q_SLOTS:
        void changeDuration(int i) { Q_EMIT durationChange((qint64)i); }

        void changePosition(int i) { Q_EMIT positionChange((qint64)i); }

        void changeEnd() { Q_EMIT endMedia(); }

    private:
        void initPlayer();

        VlcInstance *instance{};
        VlcMediaPlayer *player{};
        VlcWidgetVideo *video{};
        QStringList args{};
        QString media{};
    };

} // QCineVlcQtObject

#endif //QCINE_VLCQTOBJECT_HPP
