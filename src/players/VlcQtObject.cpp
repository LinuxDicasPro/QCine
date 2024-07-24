/**
 * Implementação do vlc-qt que usa o libvlc para reprodução de arquivos multimídia.
 */

#include "VlcQtObject.hpp"

namespace QCineVlcQtObject {
    VlcQtObject::VlcQtObject() {
        video = new VlcWidgetVideo();
        initPlayer();
    }

    /**
     * Função para adicionar um arquivo multimídia ao reprodutor.
     * @param str - Arquivo multimídia.
     */
    void VlcQtObject::setMedia(const QString &str) {
        media = str;
        player->openOnly(new VlcMedia(str, true, instance));
    }

    /**
     * Por causa das opções fornecidas via wrapper, algumas propriedades serão alteradas
     * apenas se reconstruir o player novamente.
     */
    void VlcQtObject::initPlayer() {
        if (player) {
            disconnect(player, &VlcMediaPlayer::lengthChanged, this, &VlcQtObject::changeDuration);
            disconnect(player, &VlcMediaPlayer::timeChanged, this, &VlcQtObject::changePosition);
            disconnect(player, &VlcMediaPlayer::end, this, &VlcQtObject::changeEnd);
        }

        instance = new VlcInstance(args, this);
        player = new VlcMediaPlayer(instance);
        player->setVideoWidget(video);
        video->setMediaPlayer(player);

        connect(player, &VlcMediaPlayer::lengthChanged, this, &VlcQtObject::changeDuration);
        connect(player, &VlcMediaPlayer::timeChanged, this, &VlcQtObject::changePosition);
        connect(player, &VlcMediaPlayer::end, this, &VlcQtObject::changeEnd);
    }

} // QCineVlcQtObject