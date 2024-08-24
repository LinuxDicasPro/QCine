#ifndef QCINE_VIDEOPLAYER_HPP
#define QCINE_VIDEOPLAYER_HPP

#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

namespace QCineVideoPlayer {

    class VideoPlayer : public QWidget {
    Q_OBJECT

    public:
        explicit VideoPlayer();

        QVideoSink *videoSink() { return video->videoSink(); }

    private:
        QVBoxLayout *layout{};
        QVideoWidget *video{};
    };

} // QCineVideoPlayer

#endif //QCINE_VIDEOPLAYER_HPP
