#ifndef QCINE_DEBUG_HPP
#define QCINE_DEBUG_HPP

#include <QDebug>
#include <QObject>
#include <QVariantList>

#define I(x) QString::number(x)

namespace QCineDebug {

#define GREEN       "\x1b[38;2;000;255;000m" // debug
#define RED         "\x1b[38;2;255;050;050m" // debug
#define YELLOW      "\x1b[38;2;255;255;000m" // [default] [mouse parado]
#define ORANGE      "\x1b[38;2;255;100;000m" // configuração
#define CYAN        "\x1b[38;2;000;255;255m" //
#define DARKGREEN   "\x1b[38;2;000;150;020m" // mouse movendo
#define BLUE        "\x1b[38;2;000;120;255m" //
#define VIOLET      "\x1b[38;2;120;070;255m" // reprodução
#define LIGHTRED    "\x1b[38;2;255;100;100m" // erro
#define BLUEGREEN   "\x1b[38;2;000;150;100m" //
#define YELLOWGREEN "\x1b[38;2;170;255;000m" //
#define LIGHTGREEN  "\x1b[38;2;085;255;050m" //
#define PURPLE      "\x1b[38;2;100;100;255m" //

#define MESSAGE(x) qDebug().nospace() << GREEN << "(" << RED << x << GREEN << ")" << RED << "::"
#define STR(x) qUtf8Printable(x)

    enum Color {
        Green = 0,
        Red = 1,
        Yellow = 2,
        Orange = 3,
        Cyan = 4,
        DarkGreen = 5,
        Blue = 6,
        Violet = 7,
        LightRed = 8,
        BlueGreen = 9,
        YellowGreen = 10,
        LightGreen = 11,
        Purple = 12
    };

    class Debug : public QObject {
        Q_OBJECT

    public:
        explicit Debug();

        void msg(const QString &str, const QString &name = "DEBUG", const QVariantList &args = QVariantList());

    private:
        static bool isType(const QVariant &v, const QVariant &t) { return (v.typeName() == t.typeName()); }

        QStringList listcolor{};
    };

} // QCineDebug

#endif //QCINE_DEBUG_HPP
