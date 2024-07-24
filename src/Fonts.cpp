/**
 * Classe para tentar buscar com maior precisão possível qual é a fonte padrão configurada
 * no sistema sem ter que depender dos padrões do QFont() que podem trazer resultados indesejados.
 */

#include "Fonts.hpp"

namespace QCineFonts {

    Fonts::Fonts() {
        static QRegularExpression gtkPattern("gtk-font-name=(.*)");
        static QRegularExpression qtPattern("font=\"(.*)\"");

        QVariantList confs{QVariantList({"Trolltech.conf", qtPattern}),
                           QVariantList({"gtk-3.0/settings.ini", gtkPattern})};

        foreach(QVariant fileconf, confs) {
            if (font.isEmpty()) {
                QFile file(QStandardPaths::locate(QStandardPaths::ConfigLocation, fileconf.toList().at(0).toString()));
                if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&file);
                    while (!in.atEnd()) {
                        QString line = in.readLine();
                        QRegularExpressionMatch match = fileconf.toList().at(1).toRegularExpression().match(line);
                        if (match.hasMatch()) {
                            QStringList fontInfo = match.captured(1).split(',');
                            font = fontInfo.at(0);
                            point = fontInfo.at(1).toInt();
                            QCineDebug::Debug().msg("Fonte do sistema", "Fonts",
                                                    {QString("%1, %2").arg(font, QString::number(point))});
                        }
                    }
                    file.close();
                }
            }
        }

        if (font.isEmpty()) {
            font = QFont().family();
            point = QFont().pointSize();
        }
    }

} // QCineFonts