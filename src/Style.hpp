#ifndef QCINE_STYLE_HPP
#define QCINE_STYLE_HPP

#include <QMargins>
#include <QPalette>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>

#include <SettingsManager.hpp>

namespace QCineStyle {

    enum Styles {
        Default = 0,
        Controls = 1,
        Playlist = 2,
        NoAjust = 3
    };

    enum ColorStyle {
        SystemColor = 0,
        Black = 1
    };

    class Style : public QObject {

    public:
        explicit Style();

        QString widgetStyle(Styles style = Styles::Default);

        QString dialogStyle();

        QString contextMenuStyle();

        QString styleRadiusColor(ColorStyle style = ColorStyle::SystemColor);

        QString sliderStyle();

        QMargins marginStyle();

        QMargins internalMarginStyle(Styles style = Styles::Default);

        QMargins spaceSlider();

        int spaceStyle();

        static QPalette darkTheme();

    private:
        QCineSettingsManager::SettingsManager *settingsManager{};
        QColor b = QPalette().color(QPalette::Window);
        QColor t = QPalette().color(QPalette::WindowText);
        QColor m = QPalette().color(QPalette::Highlight);
        QColor l = QPalette().color(QPalette::Light);
        QString opacity{}, border{};
    };

} // QCineStyle

#endif //QCINE_STYLE_HPP
