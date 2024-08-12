#ifndef QCINE_PLAYLISTITEM_HPP
#define QCINE_PLAYLISTITEM_HPP

#include <QDialog>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <Cover.hpp>
#include <Icon.hpp>
#include <Label.hpp>
#include <Style.hpp>

struct MediaFileInfo {
    QString file;
    QString duration;
    QString format;
    QString title;
    QString artist;
    QString info1;
    QString info2;
    QString type;
};

Q_DECLARE_METATYPE(MediaFileInfo)

namespace QCinePlaylistItem {

    class PlaylistItem : public QDialog {
    Q_OBJECT

    public:
        explicit PlaylistItem(const MediaFileInfo &media);

        QString getFile() { return str; }

        void selectColor() { this->setStyleSheet(QCineStyle::Style::itemSelectStyle()); }

        void unselectColor() { this->setStyleSheet("QDialog { border: none; background-color: none; }"); }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void playing();

#pragma clang diagnostic pop

    private:
        QCineCover::Cover *cover{};
        QVBoxLayout *infolayout{};
        QHBoxLayout *mainlayout{}, *title{}, *df{}, *art{};

        QString str{};
    };

} // QCinePlaylistItem

#endif //QCINE_PLAYLISTITEM_HPP
