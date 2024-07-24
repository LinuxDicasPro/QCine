#ifndef QCINE_BACKGROUNDTRANSITION_HPP
#define QCINE_BACKGROUNDTRANSITION_HPP

#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QWheelEvent>

#include <Debug.hpp>
#include <DefaultPath.hpp>
#include <SettingsManager.hpp>

namespace QCineBackgroundTransition {

    class BackgroundTransition : public QGraphicsView {
        Q_OBJECT

    public:
        explicit BackgroundTransition(bool noBlur = false,
                                      QSize screenSize = QCineSettingsManager::SettingsManager::res(),
                                      const QString &str = nullptr);

        void changeBackground(const QString &str = nullptr);

        void durationTransition(int i) { animation->setDuration(i); }

        void disableAnimation(bool b) { animation->setDuration(b ? 0 : settingsManager->changeEffectBackground()); }

        void changeBlur(int i) { blurEffect->setBlurRadius(i); }

    protected:
        void keyPressEvent(QKeyEvent *event) override;

        void wheelEvent(QWheelEvent *event) override;

    private Q_SLOTS:
        void effectChanged();

        void effectEnd();

    private:
        void itemPixmap(QPixmap &pixmap,
                        QGraphicsPixmapItem *item = nullptr,
                        bool random = false,
                        const QString &str = nullptr);

        [[nodiscard]] bool isNextPixmap() const { return isnextpixmap; }

        [[nodiscard]] bool isTransition() const { return istransition; }

        void isTransition(bool b) { istransition = b; }

        void isNextPixmap(bool b) { isnextpixmap = b; }

        bool istransition{false}, isnextpixmap{false};
        QCineDebug::Debug *debug{};
        QCineDefaultPath::DefaultPath *defaultPath{};
        QCineSettingsManager::SettingsManager *settingsManager{};
        QGraphicsBlurEffect *blurEffect{};
        QGraphicsOpacityEffect *opacityEffect{};
        QGraphicsPixmapItem *item1{}, *item2{};
        QGraphicsScene *scene{};
        QPropertyAnimation *animation{};
        QPixmap pixmap1{}, pixmap2{}, nextPixmap{};
        QSize screenSize{};
    };

} // QCineBackground

#endif //QCINE_BACKGROUNDTRANSITION_HPP
