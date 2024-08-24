#ifndef QCINE_VLCVIDEO_HPP
#define QCINE_VLCVIDEO_HPP

#include <QVBoxLayout>
#include <QWidget>

#include <widgets/WidgetVideo.h>

namespace QCineVlcVideo {

    class VlcVideo : public QWidget {
    Q_OBJECT

    public:
        explicit VlcVideo();

        VlcWidgetVideo *widget() { return video; }

        void setMediaPlayer(VlcMediaPlayer *player) { video->setMediaPlayer(player); }

    private:
        QVBoxLayout *layout{};
        VlcWidgetVideo *video{};
    };

} // QCineVlcVideo

#endif //QCINE_VLCVIDEO_HPP
