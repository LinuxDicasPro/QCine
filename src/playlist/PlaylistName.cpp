/**
 * QlineEdit customizado para tratar dos nomes da playlist aqui.
 */

#include "PlaylistName.hpp"

namespace QCinePlaylistName {
    PlaylistName::PlaylistName() {
        this->setText(tr("Current Playlist"));
        this->setAlignment(Qt::AlignCenter);

        dialogEditable = new QCineDialogEditable::DialogEditable();
        connect(dialogEditable, &QCineDialogEditable::DialogEditable::enterBox, this, &PlaylistName::updateEdit);
    }

    /**
     * Emitindo o sinal e atualizando o nome da playlist.
     */
    void PlaylistName::updateEdit() {
        this->setText(dialogEditable->edit()->text());
        Q_EMIT enterBox(false);
    }

    void PlaylistName::mousePressEvent(QMouseEvent *event) {
        Q_EMIT enterBox(true);

        /**
         * Preparando o diálogo editável e abrindo em tela cheia.
         * O objetivo é simular algo similar ao QAbstractItemView, só que para o QLineEdit.
         */
        dialogEditable->move(this->mapToGlobal(this->pos()) - QPoint(40, 7));
        dialogEditable->resize(this->size());
        dialogEditable->edit()->setText(this->text());
        dialogEditable->showFullScreen();

        QLabel::mousePressEvent(event);
    }

} // QCinePlaylistName
