/**
 * Modelo simplificado de lista baseado no QListWidget para armazenar as informações
 * de forma fácil e facilitar a manipulação das informações, já que tem muito recurso já pronto.
 */

#include "PlaylistModel.hpp"

namespace QCinePlaylistModel {
    PlaylistModel::PlaylistModel() {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setStyleSheet(QCineStyle::Style().playlistStyle());
    }

    /**
     * Descobrindo a localização de um arquivo armazenado na lista.
     * @param str - Arquivo para Verificação
     * @return Posição do Arquivo
     */
    int PlaylistModel::indexOf(const QString &str) {
        if (this->count() == 0)
            return (-1);

        int i{0};
        foreach(MediaFileInfo m, mediaFileList) {
            if (QString::compare(m.file, str, Qt::CaseSensitive) == 0)
                return i;
            i++;
        }

        return (-1);
    }

    /**
     * Descobrindo qual arquivo está em uma determinada posição da lista.
     * @param i - index para Localização
     * @return Arquivo da Lista
     */
    QString PlaylistModel::indexAt(int i) {
        if (this->count() == 0)
            return {};

        return mediaFileList.at(i).file;
    }

    /**
     * Populando a playlist com as informações de mídia.
     * @param list - Informações de Mídia
     */
    void PlaylistModel::insertListItem(const QStringList &list) {
        MediaFileInfo mediaFile;
        mediaFile.file = list.at(0);
        mediaFile.duration = list.at(1);
        mediaFile.format = list.at(2);
        mediaFile.title = list.at(3);
        mediaFile.artist = list.at(4);
        mediaFile.info1 = list.at(5);
        mediaFile.info2 = list.at(6);
        mediaFile.type = list.at(7);

        mediaFileList.append(mediaFile);

        auto itemW = new QCinePlaylistItem::PlaylistItem(mediaFile);
        connect(itemW, &QCinePlaylistItem::PlaylistItem::playing, [&, itemW]() {
            Q_EMIT playing(itemW->getFile());
        });

        it = new QListWidgetItem();
        it->setSizeHint(QSize(this->sizeHint().width(), itemW->sizeHint().height()));

        this->addItem(it);
        this->setItemWidget(it, itemW);
    }

    /**
     * Acessar o próximo arquivo armazenado com base em um arquivo presente na lista.
     * @param str - Arquivo da Lista
     * @return Próximo Arquivo
     */
    QString PlaylistModel::indexOfNext(const QString &str) {
        int i{indexOf(str)};
        int indexMax{this->countIndex()};
        i++;

        if (i > indexMax)
            return indexAt(0);

        if (i < 0)
            return indexAt(indexMax);

        return indexAt(i);
    }

    /**
     * Acessar o arquivo anterior armazenado com base em um arquivo presente na lista.
     * @param str - Arquivo da Lista
     * @return Arquivo Anterior
     */
    QString PlaylistModel::indexOfPrevious(const QString &str) {
        int i{indexOf(str)};
        int indexMax{this->countIndex()};
        i--;

        if (i > indexMax)
            return indexAt(0);

        if (i < 0)
            return indexAt(indexMax);

        return indexAt(i);
    }

    /**
     * Acessando o título da mídia e demais informações para o título do programa.
     * @param str - Arquivo atual sendo reproduzido.
     * @return Título
     */
    QString PlaylistModel::getName(const QString &str) {
        if (this->count() == 0)
            return str; // Em caso de não pegar o nome a tempo por alguma zebra

        return mediaFileList.at(this->indexOf(str)).title;
    }

    /**
     * Limpando os itens da lista e da playlist.
     */
    void PlaylistModel::clearList() {
        mediaFileList.clear();
        this->clear();
    }

    void PlaylistModel::loadListMetaType() {
    }

    void PlaylistModel::saveListMetaType() {
    }

} // QCinePlaylistModel