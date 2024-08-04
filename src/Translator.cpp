/**
 * Classe para definir a tradução do programa
 * conforme o idioma do sistema.
 */

#include "Translator.hpp"

namespace QCineTranslator {

    /**
     * Procura automaticamente o arquivo de tradução do programa.
     */
    void Translator::translate() {
        translator = new QTranslator(this);
        auto *debug = new QCineDebug::Debug();

        auto lang = QLocale::system().bcp47Name();
        auto trFile = QCineDefaultPath::DefaultPath().defalutPath(QString("lang/QCine_%1.qm").arg(lang));

        if (translator->load(trFile)) {
            debug->msg("Carregando tradução", "Translator", {trFile});
            QCoreApplication::installTranslator(translator);
        } else {
            debug->msg("Tradução não dísponível", "Translator", {QCineDebug::Color::LightRed});
        }

        delete debug; /** Liberando memória alocada. **/
    }
} // QCineTranslator
