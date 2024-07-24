#ifndef QCINE_PLAYLISTMODEL_HPP
#define QCINE_PLAYLISTMODEL_HPP

#include <QListWidget>

struct MediaFileInfo {
    QString file;
};

Q_DECLARE_METATYPE(MediaFileInfo)

namespace QCinePlaylistModel {

    class PlaylistModel : public QListWidget {
        Q_OBJECT

    public:
        explicit PlaylistModel();

        int countIndex() { return this->count() - 1; }

        void insertListItem(const QStringList &list);

        QString indexAt(int i);

        int indexOf(const QString &str);

        QString indexOfNext(const QString &str);

        QString indexOfPrevious(const QString &str);

        void loadListMetaType();

        void saveListMetaType();

    private:
        QList<MediaFileInfo> mediaFileList{};
    };

} // QCinePlaylistModel

#endif //QCINE_PLAYLISTMODEL_HPP
