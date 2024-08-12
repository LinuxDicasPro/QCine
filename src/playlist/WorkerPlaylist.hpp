#ifndef QCINE_WORKERPLAYLIST_HPP
#define QCINE_WORKERPLAYLIST_HPP

extern "C" {
#include <libavformat/avformat.h>
}

#include <QImage>
#include <QObject>

#include <Debug.hpp>
#include <MediaInfo.hpp>

namespace QCineWorkerPlaylist {

    class WorkerPlaylist : public QObject {
    Q_OBJECT

    public:
        explicit WorkerPlaylist();

        void setList(const QStringList &list) { strList = list; }

    public Q_SLOTS:
        void doWork();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void mediaFile(const QStringList &media);

        void finished();

#pragma clang diagnostic pop

    private:
        static bool isMediaFile(const char* filename);

        QCineDebug::Debug *debug{};
        QStringList strList{};
    };

} // QCineWorkerPlaylist

#endif //QCINE_WORKERPLAYLIST_HPP
