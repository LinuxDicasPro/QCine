/**
 * Widget com o QVideoWidget para o QMediaPlayer.
 */

#include "VideoPlayer.hpp"

namespace QCineVideoPlayer {

    VideoPlayer::VideoPlayer() {
        video = new QVideoWidget();
        layout = new QVBoxLayout(this);
        layout->setContentsMargins(QMargins());
        layout->setSpacing(0);
        layout->addWidget(video);
    }

} // QCineVideoPlayer