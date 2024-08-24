/**
 * Coleta de informações baseado no ffmpeg e QtMediaPlayer, pois pode ser que uma informação não seja coletada
 * de uma forma, então é tentado de outro jeito.
 */

#include "MediaInfo.hpp"

namespace QCineMediaInfo {

#define I(x) QString::number(x)

    MediaInfo::MediaInfo() {
        mediainfo = new QMediaPlayer();
        fileinfo = new QFileInfo();
    }

    QStringList MediaInfo::getMediaInfo(const QString &str) {
        fileinfo->setFile(str);
        mediainfo->setSource(str);
        mediainfo->play();
        mediainfo->stop();

        QString duration{}, format{}, title{}, artist{}, info1{}, info2{};
        QString type{"Audio"};

        AVFormatContext *fmt_ctx = avformat_alloc_context();
        avformat_open_input(&fmt_ctx, str.toStdString().c_str(), nullptr, nullptr);
        avformat_find_stream_info(fmt_ctx, nullptr);

        int d = mediainfo->metaData().value(QMediaMetaData::Duration).toInt();
        int secs = d > 0 ? d : int(fmt_ctx->duration);
        duration = formatDuration(secs, d > 0 ? 1000 : AV_TIME_BASE);

        qDebug() << fmt_ctx->iformat->name;

        format = QString(fmt_ctx->iformat->name).toUpper();
        if (QString::compare(format, "matroska,webm", Qt::CaseInsensitive) == 0)
            format = "Matroska";
        else if (QString::compare(format, "mov,mp4,m4a,3gp,3g2,mj2", Qt::CaseInsensitive) == 0)
            format = "MPEG4";
        else if (QString::compare(format, "ogg", Qt::CaseInsensitive) == 0)
            format = "Ogg";

        if (format.isEmpty()) {
            QString f = mediainfo->metaData().value(QMediaMetaData::FileFormat).toString();
            format = QString::compare(
                    f, "UnspecifiedFormat") == 0 || f.isEmpty() ? f : QString(fileinfo->suffix()).toUpper();
        }

        AVDictionaryEntry *tag = nullptr;
        while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            if (strcmp(tag->key, "title") == 0)
                title = tag->value;
            else if (strcmp(tag->key, "artist") == 0)
                artist = tag->value;
        }

        if (title.isEmpty())
            title = fileinfo->completeBaseName();

        for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++) {
            AVStream *stream = fmt_ctx->streams[i];
            AVCodecParameters *codec_params = stream->codecpar;
            if (codec_params->codec_type == AVMEDIA_TYPE_VIDEO and info1.isEmpty() and
                not(stream->disposition & AV_DISPOSITION_ATTACHED_PIC)) {
                int w = codec_params->width;
                int h = codec_params->height;

                info1 = QString("%1x%2 (%3)").arg(I(w), I(h), calculateAspectRatio(w, h));

                auto fps = mediainfo->metaData().value(QMediaMetaData::VideoFrameRate).toDouble();
                info2 = QString::number(fps, 'f', std::fmod(fps, 1) == 0.0 ? 0 : 2);
                type = "Video";

                if (QString::compare(info2, "0", Qt::CaseInsensitive) == 0)
                    info2 = "";

            } else if (codec_params->codec_type == AVMEDIA_TYPE_AUDIO and info1.isEmpty()) {
                int b = int(codec_params->bit_rate);
                info1 = QString::number((b > 0 ? b : mediainfo->metaData().value(
                        QMediaMetaData::AudioBitRate).toInt()) / 1000);
                info2 = QString::number(codec_params->sample_rate);

                if (QString::compare(info1, "0", Qt::CaseInsensitive) == 0)
                    info1 = "";

                if (QString::compare(info2, "0", Qt::CaseInsensitive) == 0)
                    info2 = "";
            }
        }

        qDebug() << QStringList{str, duration, format, title, artist, info1, info2, type};
        return {str, duration, format, title, artist, info1, info2, type};
    }

    /**
     * Conversão da duração da mídia para o formato hh:mm:ss e mm:ss.
     * @param duration - Duração da mídia.
     * @param base - base para converter em segundos.
     * @return Duração no Formato hh:mm:ss ou mm:ss
     */
    QString MediaInfo::formatDuration(int duration, int base) {
        int seconds = duration / base;
        QTime time((seconds / 3600) % 24, (seconds / 60) % 60, seconds % 60);
        return time.toString(seconds >= 3600 ? "hh:mm:ss" : "mm:ss");
    }

    /**
     * Cálculo do AspectRatio com base nas dimensões do arquivo multimídia.
     * @param width - Largura.
     * @param height - Altura.
     * @return AspectRatio no Formato "x:y"
     */
    QString MediaInfo::calculateAspectRatio(int width, int height) {
        int divisor{width}, b{height}, temp;

        while (b != 0) {
            temp = b;
            b = divisor % b;
            divisor = temp;
        }

        return QString::number(width / divisor) + ":" + QString::number(height / divisor);
    }

} // QCineMediaInfo