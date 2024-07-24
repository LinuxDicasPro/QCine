#ifndef QCINE_PLAYLISTNAME_HPP
#define QCINE_PLAYLISTNAME_HPP

#include <QLabel>
#include <QMouseEvent>

#include <DialogEditable.hpp>

namespace QCinePlaylistName {

    class PlaylistName : public QLabel {
        Q_OBJECT

    public:
        explicit PlaylistName();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void enterBox(bool b);

#pragma clang diagnostic pop

    protected:
        void mousePressEvent(QMouseEvent *event) override;

    private Q_SLOTS:
        void updateEdit();

    private:
        QCineDialogEditable::DialogEditable *dialogEditable{};
        QPalette originalPalette{this->palette()}, transparencyPalette{this->palette()};
    };

} // QCinePlaylistName

#endif //QCINE_PLAYLISTNAME_HPP
