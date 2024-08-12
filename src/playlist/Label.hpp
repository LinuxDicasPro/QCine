#ifndef QCINE_LABEL_HPP
#define QCINE_LABEL_HPP

#include <QLabel>

#include <Style.hpp>

namespace QCineLabel {

    class Label : public QLabel {
    Q_OBJECT

    public:
        explicit Label(const QString &l, bool b = false, int s = 0, bool i = false);
    };

} // QCineLabel

#endif //QCINE_LABEL_HPP
