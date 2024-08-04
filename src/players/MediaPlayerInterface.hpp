#ifndef QCINE_MEDIAPLAYERINTERFACE_HPP
#define QCINE_MEDIAPLAYERINTERFACE_HPP

/**
 * Interface para associar aos objetos que serão usados como engine para
 * o reprodutor multimídia.
 */

#include <QGraphicsVideoItem>
#include <QString>

namespace QCineMediaPlayerInterface {

    class MediaPlayerInterface {
    public:
        virtual void setMedia(const QString &media) = 0;
        virtual void Play() = 0;
        virtual void Resume() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;
        virtual void setSeek(int i) = 0;
//        virtual void setVolume(int i) = 0;
//        virtual void setMute(bool b) = 0;
        virtual QWidget *getVideo() = 0;
    };

} // QCineMediaPlayerInterface

#endif //QCINE_MEDIAPLAYERINTERFACE_HPP
