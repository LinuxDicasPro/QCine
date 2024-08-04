#ifndef QCINE_ICON_HPP
#define QCINE_ICON_HPP

#include <QApplication>
#include <QIcon>
#include <QObject>
#include <QPainter>
#include <QPalette>
#include <QStyle>

#include <Debug.hpp>
#include <DefaultPath.hpp>

namespace QCineIcon {

#define defIconSize 22
#define defMax 2

    enum Icons {
        Settings = 0,
        Add = 1,
        Remove = 2,
        PreviousPlaylist = 3,
        NextPlaylist = 4,
        ClearList = 5,
        Play = 6,
        Pause = 7,
        AddMenu = 8,
        Stop = 9,
        Previous = 10,
        Next = 11,
        Close = 12,
        Audio = 13,
        Video = 14,
        ItemPlay = 15
    };

    class Icon : public QObject {
        Q_OBJECT

    public:
        explicit Icon(int size = defIconSize, int max = defMax);

        QIcon setIcon(Icons icon, const QColor &color = QPalette().color(QPalette::WindowText));

    private:
        QString selectIcon(Icons icon);

        [[nodiscard]] QIcon contrastIcon(const QIcon &icon,
                                         const QColor &color = QPalette().color(QPalette::WindowText)) const;

        QCineDebug::Debug *debug{};
        QVariantList iconList{};
        int num, maxsize;
    };

} // QCineIcon

#endif //QCINE_ICON_HPP
