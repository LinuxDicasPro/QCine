/**
 * Modelo simplificado de lista baseado no QListWidget para armazenar as informações
 * de forma fácil e facilitar a manipulação das informações, já que tem muito método já pronto.
 */

#include "PlaylistModel.hpp"

namespace QCinePlaylistModel {
    PlaylistModel::PlaylistModel() = default;

    /**
     * Descobrindo a localização de um arquivo armazenado na lista.
     * @param str - Arquivo para Verificação
     * @return Posição do Arquivo
     */
    int PlaylistModel::indexOf(const QString &str) {
        if (this->count() == 0)
            return (-1);

        QList<QListWidgetItem*> items = this->findItems(str, Qt::MatchExactly);

        if (!items.isEmpty())
            return this->row(items.first());

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

        return this->item(i)->text();
    }

    /**
     * Populando a playlist com as informações de mídia.
     * @param list - Informações de Mídia
     */
    void PlaylistModel::insertListItem(const QStringList &list) {
        MediaFileInfo mediaFile;
        mediaFile.file = list.at(0);

        mediaFileList.append(mediaFile);
        this->addItem(mediaFile.file);
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

    void PlaylistModel::loadListMetaType() {
    }

    void PlaylistModel::saveListMetaType() {
    }

} // QCinePlaylistModel