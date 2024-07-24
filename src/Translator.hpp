#ifndef QCINE_TRANSLATOR_HPP
#define QCINE_TRANSLATOR_HPP

#include <QApplication>
#include <QObject>
#include <QTranslator>

#include <Debug.hpp>
#include <DefaultPath.hpp>

namespace QCineTranslator {

    class Translator : public QObject {
        Q_OBJECT

    public:
        explicit Translator();

        void translate();
    };

} // QCineTranslator

#endif //QCINE_TRANSLATOR_HPP
