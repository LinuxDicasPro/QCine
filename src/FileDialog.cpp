/**
 * QFileDialog personalizado para emitir quando ele está aberto ou fechado.
 * O objetivo é evitar a ocultação do mouse.
 */

#include "FileDialog.hpp"

namespace QCineFileDialog {

    FileDialog::FileDialog() {
        this->setWindowFlag(Qt::Drawer, true);
        this->setFileMode(QFileDialog::ExistingFiles);
        this->setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
        this->setFixedSize(QCineSettingsManager::SettingsManager().minSize());
    }

    void FileDialog::enterEvent(QEnterEvent *event) {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        Q_EMIT dialogShow(true);
        QFileDialog::enterEvent(event);
    }

    void FileDialog::showEvent(QShowEvent *event) {
        Q_EMIT dialogShow(true);
        QFileDialog::showEvent(event);
    }

    void FileDialog::hideEvent(QHideEvent *event) {
        Q_EMIT dialogShow(false);
        QFileDialog::hideEvent(event);
    }

    void FileDialog::resizeEvent(QResizeEvent *event) {
        event->ignore();
    }

} // QCineFileDialog
