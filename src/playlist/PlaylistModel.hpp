#ifndef QCINE_PLAYLISTMODEL_HPP
#define QCINE_PLAYLISTMODEL_HPP

#include <QListWidget>
#include <QScrollBar>
#include <QWheelEvent>

#include <PlaylistItem.hpp>

namespace QCinePlaylistModel {

    class PlaylistModel : public QListWidget {
    Q_OBJECT

    public:
        explicit PlaylistModel();

        int countIndex() { return this->count() - 1; }

        void insertListItem(const QStringList &list);

        QString getName(const QString &str);

        QString indexAt(int i);

        int indexOf(const QString &str);

        QString indexOfNext(const QString &str);

        QString indexOfPrevious(const QString &str);

        void clearList();

        void loadListMetaType();

        void saveListMetaType();

        QCinePlaylistItem::PlaylistItem *getItem(const QString &str) {
            return dynamic_cast<QCinePlaylistItem::PlaylistItem *>(this->itemWidget(this->item(indexOf(str))));
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void playing(const QString &str);

#pragma clang diagnostic pop

    protected:
        void wheelEvent(QWheelEvent *event) override;

    private:
        QListWidgetItem *it{};
        QList<MediaFileInfo> mediaFileList{};
    };

} // QCinePlaylistModel

#endif //QCINE_PLAYLISTMODEL_HPP
