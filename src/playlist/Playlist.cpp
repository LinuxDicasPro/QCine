/**
 * Essa vai ser a playlist do reprodutor com base no QWidget.
 * Isso permite ter total controle de como será customizada a playlist do projeto.
 */

#include "Playlist.hpp"

namespace QCinePlaylist {

    Playlist::Playlist() {
        this->setMouseTracking(true);
        this->setMinimumWidth(playlistMinWidth);
        this->setStyleSheet(QCineStyle::Style().widgetStyle(QCineStyle::Playlist));
        debug = new QCineDebug::Debug();
        playlistModel = new QCinePlaylistModel::PlaylistModel();

        /** Editor do nome da playlist atual */
        playlistName = new QCinePlaylistName::PlaylistName();
        connect(playlistName, &QCinePlaylistName::PlaylistName::enterBox, this, &Playlist::enterBox);

        /** Thread */
        thread = new QThread();
        workerPlaylist = new QCineWorkerPlaylist::WorkerPlaylist();
        workerPlaylist->moveToThread(thread);
        connect(thread, &QThread::started, workerPlaylist, &QCineWorkerPlaylist::WorkerPlaylist::doWork);
        connect(workerPlaylist, &QCineWorkerPlaylist::WorkerPlaylist::mediaFile, this, &Playlist::addPlaylist);
        connect(workerPlaylist, &QCineWorkerPlaylist::WorkerPlaylist::finished, thread, &QThread::quit);

        /** Diálogo para seleção de arquivos */
        fileDialog = new QCineFileDialog::FileDialog();
        connect(fileDialog, &QCineFileDialog::FileDialog::dialogShow, this, &Playlist::dialogShow);
        connect(fileDialog, &QFileDialog::finished, this, &Playlist::addFilesDialog);

        /** Botões */
        auto previousPlaylist = new QCineButtons::Buttons(btnIconSize, QCineIcon::PreviousPlaylist);
        auto nextPlaylist = new QCineButtons::Buttons(btnIconSize, QCineIcon::NextPlaylist);
        auto add = new QCineButtons::Buttons(btnIconSize, QCineIcon::Add);
        auto remove = new QCineButtons::Buttons(btnIconSize, QCineIcon::Remove);
        auto clear = new QCineButtons::Buttons(btnIconSize, QCineIcon::ClearList);
        connect(add, &QCineButtons::Buttons::clicked, this, &Playlist::addFiles);

        /** Layout para as playlists salvas */
        changePlaylist = new QHBoxLayout();
        changePlaylist->setContentsMargins(2, 2 ,2 ,0);
        changePlaylist->addWidget(previousPlaylist);
        changePlaylist->addWidget(playlistName);
        changePlaylist->addWidget(nextPlaylist);

        /** Layout para os botões */
        buttons = new QHBoxLayout();
        buttons->setContentsMargins(7, 0 ,7 ,0);
        buttons->setSpacing(2);
        buttons->addWidget(add);
        buttons->addWidget(remove);
        buttons->addStretch(1);
        buttons->addWidget(clear);

        /** Layout principal */
        mainlayout = new QVBoxLayout(this);
        mainlayout->setContentsMargins(0, 5 ,0 ,5);
        mainlayout->addLayout(changePlaylist);
        mainlayout->addLayout(buttons);
        mainlayout->addStretch(1);
    }

    /**
     * Adicionando arquivos multimídia validados para a plaulist do programa.
     * @param media - Lista de informações do arquivo.
     */
    void Playlist::addPlaylist(const QStringList &media) { // todo
        if (!isFirst()) {
            Q_EMIT isFirstPlay(media.at(0));
            isFirst(true);
        }

        playlistModel->insertListItem(media);
    }

    /**
     * Verifica se os arquivos foram ou não importados,
     * verificando se o dialogo não foi fechado ou cancelado.
     * @param result - Variável para verificação.
     */
    void Playlist::addFilesDialog(int result) {
        Q_EMIT finish(); // QFileDialog Fechado.

        if (result != QDialog::Rejected)
            processFiles(fileDialog->selectedFiles());
    }

    /**
     * Processando a adicionando arquivos a classe que vai obter as informações.
     * @param str - Lista de arquivos importados.
     */
    void Playlist::processFiles(const QStringList &str) {
        if (str.isEmpty())
            return;

        debug->msg("Adicionando arquivos","Playlist", {str.join(' ')});
        workerPlaylist->setList(str);
        isFirst(false);
        thread->start();
    }

    void Playlist::enterEvent(QEnterEvent *event) {
        debug->msg("Mouse posicionado na Playlist", "Playlist");
        playlistName->clearFocus(); // prevenção de erros
        this->setFocus();
        Q_EMIT noEffect(true);
        QDialog::enterEvent(event);
    }

    void Playlist::leaveEvent(QEvent *event) {
        debug->msg("Mouse posicionado fora da Playlist", "Playlist");
        playlistName->clearFocus(); // prevenção de erros
        this->setFocus();
        Q_EMIT noEffect(false);
        QDialog::leaveEvent(event);
    }

    void Playlist::mousePressEvent(QMouseEvent *event) {
        playlistName->clearFocus(); // prevenção de erros
        this->setFocus();
        QDialog::mousePressEvent(event);
    }

} // QCinePlaylist