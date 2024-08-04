#ifndef QCINE_PLAYLIST_HPP
#define QCINE_PLAYLIST_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QThread>
#include <QVBoxLayout>

#include <Buttons.hpp>
#include <Debug.hpp>
#include <FileDialog.hpp>
#include <PlaylistModel.hpp>
#include <PlaylistName.hpp>
#include <Style.hpp>
#include <WorkerPlaylist.hpp>

namespace QCinePlaylist {

    class Playlist : public QDialog {
        Q_OBJECT

    public:
        explicit Playlist();

        QCinePlaylistModel::PlaylistModel *model() { return playlistModel; }

    public Q_SLOTS:
        void addFiles() { fileDialog->exec(); }

        void processFiles(const QStringList &str);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void noEffect(bool b);

        void enterBox(bool b);

        void isFirstPlay(const QString &media);

        void dialogShow(bool b);

        void finish();

#pragma clang diagnostic pop

    protected:
        void mousePressEvent(QMouseEvent *event) override;

        void enterEvent(QEnterEvent *event) override;

        void leaveEvent(QEvent *event) override;

    private Q_SLOTS:
        void addPlaylist(const QStringList &media);

        void addFilesDialog(int result);

    private:
        void isFirst(bool b) { first = b; }

        [[nodiscard]] bool isFirst() const { return first; }

        QHBoxLayout *changePlaylist{}, *buttons{};
        QVBoxLayout *mainlayout{}, *listlayout{};

        QCineDebug::Debug *debug{};
        QCineFileDialog::FileDialog *fileDialog{};
        QCinePlaylistModel::PlaylistModel *playlistModel{};
        QCinePlaylistName::PlaylistName *playlistName{};
        QCineWorkerPlaylist::WorkerPlaylist *workerPlaylist{};
        QThread *thread{};
        bool first{false};
    };

} // QCinePlaylist

#endif //QCINE_PLAYLIST_HPP
