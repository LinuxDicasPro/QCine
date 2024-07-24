/**
 * Reprodutor de mídia padrão do QT em um objeto. O objetivo é poder incrementar mais de uma engine.
 */

#include "QMediaPlayerObject.hpp"

namespace QCineMediaPlayerObject {

    QMediaPlayerObject::QMediaPlayerObject() {
        sink = new QVideoSink();
        video = new QVideoWidget();
        auto audio = new QAudioOutput();

        player = new QMediaPlayer();
        player->setVideoOutput(sink);
        player->setAudioOutput(audio);

        connect(sink, &QVideoSink::videoFrameChanged, this, &QMediaPlayerObject::changeVideo);
        connect(player, &QMediaPlayer::durationChanged, this, &QMediaPlayerObject::changeDuration);
        connect(player, &QMediaPlayer::positionChanged, this, &QMediaPlayerObject::changePosition);
        connect(player, &QMediaPlayer::mediaStatusChanged, this, &QMediaPlayerObject::changeStatus);
    }

    /**
     * Setando um arquivo multimídia para a reprodução.
     * @param str - Local do arquivo multimídia.
     */
    void QMediaPlayerObject::setMedia(const QString &str) {
        player->setSource(QUrl());
        player->setSource(QUrl::fromLocalFile(str));
    }

    /**
     * Capturando frame por frame para alterar certas propriedades de vídeo como o ângulo.
     * @param frame - Frame de vídeo.
     */
    void QMediaPlayerObject::changeVideo(const QVideoFrame &frame) {
        QVideoFrame frame1 = frame;
        frame1.setRotationAngle(QVideoFrame::Rotation0);
        video->videoSink()->setVideoFrame(frame1);
    }

    /**
     * Verificando os status de reprodução para emitir as ações necessárias.
     * @param st - status de reprodução.
     */
    void QMediaPlayerObject::changeStatus(QMediaPlayer::MediaStatus st) {
        if (st == QMediaPlayer::EndOfMedia)
            Q_EMIT endMedia();
    }

} // QCineMediaPlayerObject