/**
 * Depuração personalizada para o projeto.
 * O objetivo é facilitar o debug pela linha de comando.
 */

#include "Debug.hpp"

namespace QCineDebug {

    Debug::Debug() {
        (void) Color::Green;
        (void) Color::Red;
        (void) Color::Yellow;
        (void) Color::Orange;
        (void) Color::Cyan;
        (void) Color::DarkGreen;
        (void) Color::Blue;
        (void) Color::Violet;
        (void) Color::LightRed;
        (void) Color::BlueGreen;
        (void) Color::YellowGreen;
        (void) Color::LightGreen;
        (void) Color::Purple;

        listcolor = QStringList({
                                        GREEN,        // 0
                                        RED,          // 1
                                        YELLOW,       // 2
                                        ORANGE,       // 3
                                        CYAN,         // 4
                                        DARKGREEN,    // 5
                                        BLUE,         // 6
                                        VIOLET,       // 7
                                        LIGHTRED,     // 8
                                        BLUEGREEN,    // 9
                                        YELLOWGREEN,  // 10
                                        LIGHTGREEN,   // 11
                                        PURPLE        // 12
                                });
    }

    /**
     * Mensagem com parâmetro.
     * @param str - Texto da mensagem.
     * @param name - Especificação da mensagem que substitui o padrão DEBUG.
     * @param args - Argumentos extras para o debug, não importa a ordem.
     */
    void Debug::msg(const QString &str, const QString &name, const QVariantList &args) {

        QString parm{}, p{}, fcolor{}, scolor{};
        int i{0};

        foreach(QVariant arg, args) {
            if (isType(arg, QString())) {
                parm = args.at(i).toString();
                p = ": ";
            } else if (isType(arg, Color())) {
                if (fcolor.isEmpty())
                    fcolor = listcolor.at(arg.toInt());
                else if (scolor.isEmpty())
                    scolor = listcolor.at(arg.toInt());
            }
            i++;
        }

        MESSAGE(STR(name)) << STR(fcolor.isEmpty() ? listcolor.at(int(Color::Yellow)) : fcolor)
                           << STR(QString("%1%2").arg(str, p))
                           << STR((scolor.isEmpty() && !parm.isEmpty()) ? listcolor.at(int(Color::Yellow)) : scolor)
                           << STR(parm) << "\x1b[m";
    }

} // QCineDebug
