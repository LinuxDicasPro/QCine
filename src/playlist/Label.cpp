/**
 * Labels customizados para os itens da playlist, tanto para texto quanto para imagem.
 */

#include "Label.hpp"

namespace QCineLabel {

#define msize 20
#define xsize 28
#define mrad 10
#define xrad 14

    Label::Label(const QString &l, bool b, int s, bool i)  {
        if (s > 0)
            this->setMinimumHeight(xsize);
        else
            this->setMinimumHeight(msize);

        QFont font;
        font.setPointSize(font.pointSize() + s);
        font.setBold(b);
        font.setItalic(i);
        this->setFont(font);
        this->setText(l);
        this->setStyleSheet(QCineStyle::Style::labelStyle(s > 0 ? xrad : mrad));
    }

} // QCineLabel