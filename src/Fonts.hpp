#ifndef QCINE_FONTS_HPP
#define QCINE_FONTS_HPP

#include <QFile>
#include <QFont>
#include <QObject>
#include <QRegularExpression>
#include <QStandardPaths>

#include <Debug.hpp>

namespace QCineFonts {

    class Fonts : public QObject {
        Q_OBJECT

    public:
        explicit Fonts();

        QFont getFont() { return {font, point}; }

    private:
        QString font{};
        int point{0};
    };

} // QCineFonts

#endif //QCINE_FONTS_HPP
