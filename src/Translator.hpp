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
        using QObject::QObject;

        void translate();

    private:
        QTranslator *translator{};
    };

} // QCineTranslator

#endif //QCINE_TRANSLATOR_HPP
