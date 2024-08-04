/**
 * Essa é a parte que serão definido os ícones do programa. Os ícones servirão para
 * o menu de contexto e botões do programa.
 */

#include "Icon.hpp"

namespace QCineIcon {

    Icon::Icon(int size, int max) : num(size), maxsize(max) {
        debug = new QCineDebug::Debug();

        iconList = {
                QVariantList {"settings", QStyle::SP_ArrowRight},
                QVariantList {"add", QStyle::SP_FileDialogNewFolder},
                QVariantList {"remove", QStyle::SP_DialogCancelButton},
                QVariantList {"previousplaylist", QStyle::SP_ArrowLeft},
                QVariantList {"nextplaylist", QStyle::SP_ArrowRight},
                QVariantList {"clearlist", QStyle::SP_DialogDiscardButton},
                QVariantList {"play", QStyle::SP_MediaPlay},
                QVariantList {"pause", QStyle::SP_MediaPause},
                QVariantList {"addmenu", QStyle::SP_FileDialogNewFolder},
                QVariantList {"stop", QStyle::SP_MediaStop},
                QVariantList {"previous", QStyle::SP_MediaSeekBackward},
                QVariantList {"next", QStyle::SP_MediaSeekForward},
                QVariantList {"close", QStyle::SP_DialogCloseButton},
                QVariantList {"audio", QStyle::SP_MediaPlay},
                QVariantList {"video", QStyle::SP_MediaPlay},
                QVariantList {"itemplay", QStyle::SP_MediaPlay}
        };
    }

    /**
     * Função para buscar o ícone do programa caso ele exista.
     * @param icon - Ícone a ser selecionado.
     * @return QString
     */
    QString Icon::selectIcon(Icons icon) {
        auto local = QCineDefaultPath::DefaultPath().defalutPath("icons");

        if (!local.isEmpty()) {
            QString ico = QString("%1/%2.svg").arg(local, iconList.at(int(icon)).toList().at(0).toString());

            if (QFileInfo::exists(ico)) {
                debug->msg("Selecionando ícone", "Icon", {ico});
                return ico;
            }
        }

        return {};
    }

    /**
     * Contrastando os ícones conforme o tema do programa.
     * @param icon - Ícone a receber o contraste.
     * @param color - Cor opcional, se necessário.
     * @return QIcon
     */
    QIcon Icon::contrastIcon(const QIcon &icon, const QColor &color) const {
        QPixmap themed_pixmap(num + maxsize, num + maxsize);
        themed_pixmap.fill(Qt::transparent);

        /** Ícone original em tons de cinza */
        QPainter painter(&themed_pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setRenderHint(QPainter::LosslessImageRendering, true);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawPixmap(0, 0, icon.pixmap(num + maxsize, num + maxsize));

        /** Pintando o ícone com a cor do tema do sistema */
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(themed_pixmap.rect(), color);
        painter.end();

        return {themed_pixmap};
    }

    /**
     * Função para setar o ícone dos botões e menu.
     * @param icon - Ícone a ser setado.
     * @param color - Cor opcional se necessário.
     * @return QIcon
     */
    QIcon Icon::setIcon(Icons icon, const QColor &color) {
        QString ico = selectIcon(icon);

        if (ico.isEmpty())
            return QApplication::style()->standardIcon(
                    iconList.at(int(icon)).toList().at(1).value<QStyle::StandardPixmap>());

        return contrastIcon(QIcon(ico), color);
    }

} // QCineIcon