#ifndef QCINE_MEDIAINFO_HPP
#define QCINE_MEDIAINFO_HPP

#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QObject>

extern "C" {
#include <libavformat/avformat.h>
}

namespace QCineMediaInfo {

    class MediaInfo : public QObject {
    Q_OBJECT

    public:
        explicit MediaInfo();

        QStringList getMediaInfo(const QString &str);

    private:
        static QString formatDuration(int duration, int base);

        static QString calculateAspectRatio(int width, int height);

        QFileInfo *fileinfo{};
        QMediaPlayer *mediainfo{};
    };

} // QCineMediaInfo

#endif //QCINE_MEDIAINFO_HPP
