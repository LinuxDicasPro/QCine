#ifndef QCINE_CHECKMOUSE_HPP
#define QCINE_CHECKMOUSE_HPP

#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QPoint>

#include <Debug.hpp>
#include <SettingsManager.hpp>

namespace QCineCheckMouse {

    class CheckMouse : public QObject {
        Q_OBJECT

    public:
        explicit CheckMouse();

        void hideEffect() { hideTimer->start(); };

        void mousePos(QPoint point) { lastMousePos = point; }

        void noMouseCheck(bool b) { stopCheck = b; }

        void isAlready(bool b) { alreadyMove = b; }

        void isContextMenu(bool b) { contextMenu = b; }

        void isDialog(bool b) { dialog = b; }

    public Q_SLOTS:
        void setHideTimer(int i) { changeHideTimer = i; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void movingMouse(bool b);

#pragma clang diagnostic pop

    private Q_SLOTS:
        void checkMouseMovement();

    private:
        [[nodiscard]] bool isDialog() const { return dialog; }

        [[nodiscard]] bool isContextMenu() const { return contextMenu; }

        [[nodiscard]] bool isNoMouseCheck() const { return stopCheck; }

        [[nodiscard]] bool isMouseMove() const { return mouseMove; }

        [[nodiscard]] bool isAlready() const { return alreadyMove; }

        void isMouseMove(bool b) { mouseMove = b; }

        void noMovingMouse();

        QCineDebug::Debug *debug{};
        QTimer *mouseTimer{}, *hideTimer{};
        QPoint lastMousePos{}, currentPos{};
        bool mouseMove{false}, stopCheck{false}, alreadyMove{false}, contextMenu{false}, dialog{false};
        int changeHideTimer{};
    };

} // QCineCheckMouse

#endif //QCINE_CHECKMOUSE_HPP
