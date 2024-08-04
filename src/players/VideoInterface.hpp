#ifndef QCINE_VIDEOINTERFACE_HPP
#define QCINE_VIDEOINTERFACE_HPP

#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

#include <widgets/WidgetVideo.h>

/**
 * Não é uma interface de fato, mas todos os widgets de vídeo
 * vou centralizar aqui caso seja possível.
 */

namespace QCineVideoInterface {

    /** Layout para o QVideoWidget */
    class VideoWidget : public QWidget {
        Q_OBJECT

    public:
        explicit VideoWidget() {
            video = new QVideoWidget();
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(QMargins());
            layout->setSpacing(0);
            layout->addWidget(video);
        }

        QVideoSink *videoSink() { return video->videoSink(); }

    private:
        QVBoxLayout *layout{};
        QVideoWidget *video{};
    };

    /** Layout para o VlcWidgetVideo */
    class VlcVideo : public QWidget {
    Q_OBJECT

    public:
        explicit VlcVideo() {
            video = new VlcWidgetVideo();
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(QMargins());
            layout->setSpacing(0);
            layout->addWidget(video);
        }

        VlcWidgetVideo *widget() { return video; }

        void setMediaPlayer(VlcMediaPlayer *player) { video->setMediaPlayer(player); }

    private:
        QVBoxLayout *layout{};
        VlcWidgetVideo *video{};
    };

} // QCineVideoInterface

#endif //QCINE_VIDEOINTERFACE_HPP
