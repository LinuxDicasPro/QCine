/**
 * Itens para o preenchimento da playlist.
 * Cada item da playlist será um QWidget desse.
 */

#include "PlaylistItem.hpp"

namespace QCinePlaylistItem {

#define iconSize 48

    PlaylistItem::PlaylistItem(const MediaFileInfo &media) : str(media.file) {
        this->setStyleSheet("QDialog { border: none; background-color: none; }");

        QString s1{media.type == "Video" or media.info1.isEmpty() ? "" : " kbps"};
        QString s2{media.info2.isEmpty() ? "" : media.type == "Video" ? " fps" : " Hz"};
        QString p1{media.info1.isEmpty() and media.info2.isEmpty() ? "" : "     "};
        QString p2{media.info1.isEmpty() or media.info2.isEmpty() ? "" : "     "};

        /** Layout para o título */
        title = new QHBoxLayout();
        title->setContentsMargins(QMargins());
        title->setSpacing(0);
        title->addWidget(new QCineLabel::Label(media.title, true, 4));
        title->addStretch(1);

        /** Layout da duração e formato */
        df = new QHBoxLayout();
        df->setContentsMargins(QMargins());
        df->setSpacing(0);
        df->addWidget(new QCineLabel::Label(media.duration, true, (-1)));
        df->addSpacing(5);
        df->addWidget(new QCineLabel::Label(media.format + p1 + media.info1 + s1 + p2 + media.info2 + s2, true, (-1)));
        df->addStretch(1);

        /** Layout para o artista e se não houver, vai o nome do diretório */
        art = new QHBoxLayout();
        art->setContentsMargins(QMargins());
        art->setSpacing(0);
        if (media.artist.isEmpty())
            art->addWidget(new QCineLabel::Label(QFileInfo(media.file).absoluteDir().dirName(), false, 0, true));
        else
            art->addWidget(new QCineLabel::Label(media.artist, true, 0, true));
        art->addStretch(1);

        QPixmap pixmap = QCineIcon::Icon(iconSize).setIcon(
                media.type == "Video" ? QCineIcon::Video : QCineIcon::Audio).pixmap(iconSize, iconSize);
        cover = new QCineCover::Cover(pixmap);
        connect(cover, &QCineCover::Cover::playing, this, &PlaylistItem::playing);

        /** Layout de informações */
        infolayout = new QVBoxLayout();
        infolayout->addStretch(1);
        infolayout->addLayout(art);
        infolayout->addLayout(title);
        infolayout->addLayout(df);
        infolayout->addStretch(1);

        /** Layout principal */
        mainlayout = new QHBoxLayout(this);
        mainlayout->setContentsMargins(5, 5, 0, 5);
        mainlayout->addWidget(cover);
        mainlayout->addLayout(infolayout);
    }

} // QCinePlaylistItem