/**
 * Widget com o VlcWidgetVideo para o VlcMediaPlayer.
 */

#include "VlcVideo.hpp"

namespace QCineVlcVideo {

    VlcVideo::VlcVideo() {
        video = new VlcWidgetVideo();
        layout = new QVBoxLayout(this);
        layout->setContentsMargins(QMargins());
        layout->setSpacing(0);
        layout->addWidget(video);
    }

} // QCineVlcVideo