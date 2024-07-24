/**
 * Classe para definir qual a engine vai ser usado para a reprodução.
 */

#include "Player.hpp"

namespace QCinePlayer {

    Player::Player() {
        /** Debud e configuração */
        debug = new QCineDebug::Debug();
        settingsManager = new QCineSettingsManager::SettingsManager();
        screenSaver = new ScreenSaver();

        /** Engine do QMediaPlayer */
        mediaPlayer = new QCineMediaPlayerObject::QMediaPlayerObject();
        connect(mediaPlayer, &QCineMediaPlayerObject::QMediaPlayerObject::positionChange, this, &Player::positionChange);
        connect(mediaPlayer, &QCineMediaPlayerObject::QMediaPlayerObject::durationChange, this, &Player::durationChange);
        connect(mediaPlayer, &QCineMediaPlayerObject::QMediaPlayerObject::endMedia, this, &Player::endMedia);

        /** Engine do VLC-QT6 */
        vlcPlayer = new QCineVlcQtObject::VlcQtObject();
        connect(vlcPlayer, &QCineVlcQtObject::VlcQtObject::positionChange, this, &Player::positionChange);
        connect(vlcPlayer, &QCineVlcQtObject::VlcQtObject::durationChange, this, &Player::durationChange);
        connect(vlcPlayer, &QCineVlcQtObject::VlcQtObject::endMedia, this, &Player::endMedia);

        selectEngine();
    }

    /**
     * Função para adicionar arquivos multimídia pra já ir sendo reproduzido.
     * @param media - Arquivo a ser reproduzido.
     */
    void Player::play(const QString &media) {
        if (!media.isEmpty()) {
            player->setMedia(media);
            currentFile = media;
        } else {
            if (!isPlaying())
                player->setMedia(currentFile);
        }

        if (isPlaying() && media.isEmpty()) {
            debug->msg("Continuando reprodução", "Player");
            player->Resume();
        } else {
            debug->msg("Iniciando reprodução", "Player");
            player->Play();
        }

        isVideo();
        isPlaying(true);
        isPausing(false);

        if (!isBlockScreenSaver()) {
            debug->msg("Bloqueio de suspensão de tela e screensaver", "Player");
            screenSaver->disable();
            isBlockScreenSaver(true);
        }
    }

    /**
     * Função para pausar a reprodução multimídia.
     */
    void Player::pause() {
        debug->msg("Pausando reprodução", "Player");
        player->Pause();
        isPausing(true);
    }

    /**
     * Função para parar a reprodução multimídia.
     */
    void Player::stop() {
        player->Stop();
        isPlaying(false);
        isPausing(false);
        Q_EMIT checkVideo(false);

        if (isBlockScreenSaver()) {
            debug->msg("Desbloqueio de suspensão de tela e screensaver", "Player");
            screenSaver->enable();
            isBlockScreenSaver(false);
        }
    }

    /**
     * Verificação de qual engine de reprodução será usada pelo reprodutor.
     */
    void Player::selectEngine() {
        auto s = settingsManager->videoEngine();
        if (s == QCineSettingsManager::UseVlcQT) {
            debug->msg("Usando VlcQT", "Player");
            player = dynamic_cast<QCineMediaPlayerInterface::MediaPlayerInterface*>(vlcPlayer);
        } else {
            debug->msg("Usando QMediaPlayer", "Player");
            player = dynamic_cast<QCineMediaPlayerInterface::MediaPlayerInterface*>(mediaPlayer);
        }
    }

    /**
     * Função para mudar a engine usarda para reprodução de arquivos multimídia.
     */
    void Player::changeEngine() {
        stop();
        selectEngine();
    }

    /**
     * Implementação própria e precisa para verificação de vídeo.
     */
    void Player::isVideo() {
        AVFormatContext* pFormatContext = avformat_alloc_context();
        if (!pFormatContext) {
            Q_EMIT checkVideo(false);
            return;
        }

        if (avformat_open_input(&pFormatContext, currentFile.toStdString().c_str(), nullptr, nullptr) != 0) {
            avformat_free_context(pFormatContext);
            Q_EMIT checkVideo(false);
            return;
        }

        if (avformat_find_stream_info(pFormatContext, nullptr) < 0) {
            avformat_close_input(&pFormatContext);
            avformat_free_context(pFormatContext);
            Q_EMIT checkVideo(false);
            return;
        }

        bool hasValidVideo = false;
        for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
            AVCodecParameters* codecParameters = pFormatContext->streams[i]->codecpar;
            if (codecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
                if (codecParameters->width > 0 && codecParameters->height > 0) {
                    hasValidVideo = true;
                    break;
                }
            }
        }

        Q_EMIT checkVideo(hasValidVideo);
        avformat_close_input(&pFormatContext);
        avformat_free_context(pFormatContext);
    }

} // QCinePlayer
