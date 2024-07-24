#ifndef QCINE_CLICKMAPPER_HPP
#define QCINE_CLICKMAPPER_HPP

#include <QObject>
#include <QTimer>

#include <Debug.hpp>

namespace QCineClickMapper {

    class ClickMapper : public QObject {
        Q_OBJECT

    public:
        explicit ClickMapper(QObject *parent = nullptr);

    public Q_SLOTS:
        void mapClicks();

        void isBlockClick(bool b) { blockClick = b; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void singleClick();
        void doubleClick();

#pragma clang diagnostic pop

    private:
        [[nodiscard]] bool isBlockClick() const { return blockClick; }

        void checkClicks();

        QCineDebug::Debug *debug{};
        int m_clickCount{0};
        bool blockClick{false};
    };

} // QCineClickMapper

#endif //QCINE_CLICKMAPPER_HPP
