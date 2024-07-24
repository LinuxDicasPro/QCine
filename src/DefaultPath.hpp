#ifndef QCINE_DEFAULTPATH_HPP
#define QCINE_DEFAULTPATH_HPP

#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QRegularExpression>

#include <Debug.hpp>

namespace QCineDefaultPath {

    class DefaultPath : public QObject {
        Q_OBJECT

    public:
        explicit DefaultPath();

        QString defalutPath(const QString &str);

        int countFiles(const QString &str);

    private:
        QString findPath(const QString &str);

        QCineDebug::Debug *debug{};
        QString dir{QCoreApplication::applicationDirPath()}, oldDir{QCoreApplication::applicationDirPath()};
        QString px{"/usr/local/share/qcine"};
        QString newPx{"/usr/share/qcine"};
    };

} // QCineDefaultPath

#endif //QCINE_DEFAULTPATH_HPP
