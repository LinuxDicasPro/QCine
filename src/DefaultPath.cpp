/**
 * Classe que será usada para encontrar os arquivos necessários para o programa.
 */

#include "DefaultPath.hpp"

namespace QCineDefaultPath {

    DefaultPath::DefaultPath() {
        debug = new QCineDebug::Debug();
        static const QRegularExpression regex("\\/(?:.(?!\\/))+$");
        oldDir = oldDir.remove(regex);

        oldDir += '/';  // Controle
        dir += '/';    // de erros
    }

    /**
     * Pesquisa de arquivos ou diretórios.
     * @param str - Arquivo ou diretório a ser localizado.
     * @return QString
     */
    QString DefaultPath::findPath(const QString &str) {
        auto defDir = QString("%1%2").arg((QFileInfo::exists(dir + str)) ? dir : oldDir, str);

        if (!QFileInfo::exists(defDir))
            return QString("%1%2").arg((QFileInfo::exists(px + str)) ? px : newPx, str);

        return defDir;
    }

    /**
     * Função que retorna o diretório a ser usado, caso tenha sido encontrado.
     * @param str - Localização do subdiretório e arquivo que servirá como base na pesquisa.
     * @return QString
     */
    QString DefaultPath::defalutPath(const QString &str) {
        auto defDir = findPath(str);

        if (QFileInfo::exists(defDir)) {
            debug->msg(QString("Diretório para %1").arg(str), "DefaultPath", {defDir});
            return defDir;
        }

        debug->msg(QString("Nenhum diretório definido para %1").arg(str), "DefaultPath",{QCineDebug::Color::LightRed});
        return {};
    }

    /**
     * Função que contabiliza o número de arquivos em um diretório.
     * @param str - Local para a contagem.
     * @return int
     */
    int DefaultPath::countFiles(const QString &str) {
        auto defDir = findPath(str);

        if (QFileInfo::exists(defDir)) {
            QDir local(defDir);
            local.setFilter(QDir::Files);

            int i = int(local.entryList().size());
            debug->msg(QString("Número de arquivos em %1").arg(str), "DefaultPath", {I(i)});

            return i;
        }
        return 0;
    }

} // QCineDefaultPath