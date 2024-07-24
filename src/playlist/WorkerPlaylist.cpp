/**
 * Thread especial para não correr o risco de atrasar o programa coletando as informações.
 * Essa classe irá coletar todas as informações necessárias.
 */

#include "WorkerPlaylist.hpp"

namespace QCineWorkerPlaylist {

    WorkerPlaylist::WorkerPlaylist() {
        debug = new QCineDebug::Debug();
    }

    /**
     * Função para buscar as informações dos arquivos multimídia.
     */
    void WorkerPlaylist::doWork() {
        debug->msg("Verificando e processando arquivos adicionados", "WorkerPlaylist");

        foreach(QString str, strList) {
            QImage image(str); // Imagens passam pela verificação

            if(isMediaFile(str.toStdString().c_str()) && image.isNull()) {


                Q_EMIT mediaFile({str});
            }
        }

        debug->msg("Finalizando verificação", "WorkerPlaylist");
        Q_EMIT finished();
    }

    /**
     * Usando libavformat para verificar com mais precisão e performance possível se o arquivo
     * verificado é um formato multimídia válido.
     * @param filename - Arquivo a ser verificado.
     * @return bool
     */
    bool WorkerPlaylist::isMediaFile(const char *filename)  {
        AVFormatContext *pFormatContext = avformat_alloc_context();
        if (!pFormatContext)
            return false;

        if (avformat_open_input(&pFormatContext, filename, nullptr, nullptr) != 0) {
            avformat_free_context(pFormatContext);
            return false;
        }

        avformat_close_input(&pFormatContext);
        avformat_free_context(pFormatContext);
        return true;
    }

} // QCineWorkerPlaylist