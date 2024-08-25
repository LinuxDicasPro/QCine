/**
 * Classe para centralizar o estilo do programa em um lugar só.
 * O objetivo é facilitar a customização do projeto.
 * A classe foi feita para ter sempre alocação estática.
 *
 * Otimização de Performance: 2024/07/06
 */

#include "Style.hpp"

namespace QCineStyle {

#define defMargin 0
#define roundMargin 5
#define gradientMargin 10
#define ajustTransparency 55
#define styleRadiusSize 18
#define defSpaceSlider 5
#define spaceRoundSlider 10
#define pLabel 100
#define pSelect 80

    Style::Style() {
        settingsManager = new QCineSettingsManager::SettingsManager();

        auto opacy = I(settingsManager->opacityTheme());
        auto opacyg = I(opacy.toInt() - ajustTransparency);
        opacity = settingsManager->programTheme() == QCineSettingsManager::Gradient ? opacyg : opacy;

        border = QString("border: %4px outset rgb(%1, %2, %3);").arg(
                I(t.red()), I(t.green()), I(t.blue()), I(settingsManager->borderSize()));
    }

    /**
     * Estilização dos widgets dos controles de reprodução e playlist do programa.
     * @param style - Conferir se é controle ou playlist.
     * @return Estilo dos Controles e Playlist
     */
    QString Style::widgetStyle(Styles style) {
        QString color{QString("rgba(%1, %2, %3, %4)").arg(I(b.red()), I(b.green()), I(b.blue()), opacity)};

        if (settingsManager->programTheme() == QCineSettingsManager::Gradient) {
            if (style == QCineStyle::Controls)
                color = QString("rgb(%1, %2, %3)").arg(I(b.red()), I(b.green()), I(b.blue()));
            else if (style == QCineStyle::Playlist)
                color = QString("rgba(%1, %2, %3, %4)").arg(I(b.red()), I(b.green()), I(b.blue()), opacity);
        }

        if ((ColorStyle) settingsManager->colorTheme() == ColorStyle::Black) {
            if (settingsManager->programTheme() == QCineSettingsManager::Gradient && style == QCineStyle::Controls)
                color = "black";
            else
                color = QString("rgba(0, 0, 0, %1)").arg(opacity);
        }

        if (settingsManager->programTheme() == QCineSettingsManager::Gradient) {
            if (style == QCineStyle::Controls) {
                return QString("QDialog {"
                               "    background-color: qlineargradient(x1:0, y1:1, x2:0, y2:0,"
                               "                                      stop:0 %1, stop:1 transparent);"
                               "}").arg(color);
            }
            if (style == QCineStyle::Playlist) {
                return QString("QDialog {"
                               "    background-color: %1;"
                               "    border-radius: 15px;"
                               "%2 }").arg(color, border);
            }
        }

        if (settingsManager->programTheme() == QCineSettingsManager::Rounded) {
            return QString("QDialog {"
                           "    background-color: %2;"
                           "    border-radius: 15px;"
                           "%1 }").arg(border, color);
        }

        return QString("QDialog {"
                       "    background-color: %5;"
                       "    border-%4: 1px outset rgb(%1, %2, %3);"
                       "}").arg(I(l.red()), I(l.green()), I(l.blue()),
                                style == Styles::Playlist ? "left" : "top", color);
    }

    /**
     * Estilização do tema das configurações e demais caixas de diálogos.
     * @return Estilo do Fundo
     */
    QString Style::dialogStyle() {
        QString color{QString("rgba(%1, %2, %3, %4)").arg(I(b.red()), I(b.green()), I(b.blue()), opacity)};

        if ((ColorStyle) settingsManager->colorTheme() == ColorStyle::Black)
            color = QString("rgba(0, 0, 0, %1)").arg(opacity);


        if (settingsManager->programTheme() != QCineSettingsManager::Default) {
            return QString("QDialog {"
                           "    background-color: %1;"
                           "    border-radius: 15px;"
                           "%2 }").arg(color, border);
        }

        return QString("QDialog {"
                       "    background-color: %4;"
                       "    border-right: 1px solid rgb(%1, %2, %3);"
                       "    border-bottom: 1px solid rgb(%1, %2, %3);"
                       "}").arg(I(l.red()), I(l.green()), I(l.blue()), color);
    }

    /**
     * Customização para o menu de contexto do programa.
     * @return Estilo do Menu
     */
    QString Style::contextMenuStyle() {
        QString color{QString("rgba(%1, %2, %3, %4)").arg(I(b.red()), I(b.green()), I(b.blue()), opacity)};

        QString cborder{};
        if (settingsManager->borderSize() > QCineSettingsManager::Default)
            cborder = QString("border: 1px outset rgb(%1, %2, %3);").arg(I(t.red()), I(t.green()), I(t.blue()));

        if ((ColorStyle) settingsManager->colorTheme() == ColorStyle::Black)
            color = QString("rgba(0, 0, 0, %1)").arg(opacity);

        if (settingsManager->programTheme() != QCineSettingsManager::Default) {
            return QString("QMenu {"
                           "    background-color: %4;"
                           "    border-radius: 15px;"
                           "%5 }"
                           "QMenu::separator {}"
                           "QMenu::item {"
                           "    margin: 3px;"
                           "    padding: 6px 12px;"
                           "}"
                           "QMenu::item:selected {"
                           "    background-color: rgba(%1, %2, %3, 150);"
                           "    border-radius: 12px;"
                           "}"
                           "QMenu::icon {"
                           "    margin-right: 12px;"
                           "}").arg(I(m.red()), I(m.green()), I(m.blue()), color, cborder);
        }

        return QString("QMenu {"
                       "    background-color: %7;"
                       "    border: 1px solid rgba(%4, %5, %6, %8);"
                       "}"
                       "QMenu::separator {}"
                       "QMenu::item {"
                       "    padding: 6px 12px;"
                       "}"
                       "QMenu::item:selected {"
                       "    background-color: rgba(%1, %2, %3, 150);"
                       "}"
                       "QMenu::icon {"
                       "    margin-right: 12px;"
                       "}").arg(I(m.red()), I(m.green()), I(m.blue()),
                                I(l.red()), I(l.green()), I(l.blue()), color, opacity);
    }

    /**
     * Estilo para pintar os QRadioButtons conforme o tema de cores dos controles.
     * @param style - Estilo de cor.
     * @return Estilo dos Botões de Cor
     */
    QString Style::styleRadiusColor(ColorStyle style) {
        QString color{QString("rgb(%1, %2, %3)").arg(I(b.red()), I(b.green()), I(b.blue()))};

        if (style == ColorStyle::Black)
            color = "black";

        return QString("QRadioButton::indicator {"
                       "    background-color: %1;"
                       "    width: %2px;"
                       "    height: %3px;"
                       "}"
                       "QRadioButton::indicator:checked {"
                       "border: 1px outset rgb(%4, %5, %6);"
                       "}").arg(color, I(styleRadiusSize), I(styleRadiusSize), I(m.red()), I(m.green()), I(m.blue()));
    }

    /**
     * Esquema normal de cores para o slider de reprodução.
     * @return Estilo do Slider
     */
    QString Style::sliderStyle() {
        return QString("QSlider::groove {"
                       "    background-color: transparent;"
                       "    border: 1px solid rgb(%1, %2, %3);"
                       "    border-radius: 2px;"
                       "    height: 2px;"
                       "}"
                       "QSlider::handle {"
                       "    background-color: transparent;"
                       "    border: 1px solid transparent;"
                       "    width: 4px;"
                       "}"
                       "QSlider::sub-page {"
                       "    background-color: rgb(%4, %5, %6);"
                       "    border: 1px solid rgb(%4, %5, %6);"
                       "    border-radius: 2px;"
                       "}"
                       "QSlider::sub-page:disabled {"
                       "    background-color: transparent;"
                       "    border: none;"
                       "}").arg(I(l.red()), I(l.green()), I(l.blue()), I(m.red()), I(m.green()), I(m.blue()));
    }

    /**
     * Esquema de cores para o controle de volume.
     * @return Estilo do Volume
     */
    QString Style::volumeStyle() {
        return QString("QSlider {"
                       "    height: 32px;"
                       "}"
                       "QSlider::groove {"
                       "    background-color: transparent;"
                       "    border: 1px solid rgb(%1, %2, %3);"
                       "    border-radius: 2px;"
                       "    height: 2px;"
                       "}"
                       "QSlider::handle {"
                       "    border: 1px solid rgb(%7, %8, %9);"
                       "    background-color: rgb(%4, %5, %6);"
                       "    width: 16px;"
                       "    margin: -8 -1;"
                       "    border-radius: 9px;"
                       "}"
                       "QSlider::sub-page {"
                       "    background-color: rgb(%4, %5, %6);"
                       "    border: 1px solid rgb(%4, %5, %6);"
                       "    border-radius: 2px;"
                       "}"
                       "QSlider::sub-page:disabled {"
                       "    background-color: transparent;"
                       "    border: none;"
                       "}").arg(I(l.red()), I(l.green()), I(l.blue()), I(m.red()), I(m.green()), I(m.blue()),
                                I(60), I(112), I(132));
    }

    /**
     * Função para customizar o label usado para mostrar as informações da mídia importada.
     * @return Estilo do Fundo do Texto
     */
    QString Style::labelStyle(int i) {
        return QString("QLabel {"
                       "    background-color: rgba(0, 0, 0, %1);"
                       "    border-radius: %2px;"
                       "    padding-left: 10px;"
                       "    padding-right: 10px;"
                       "}").arg(I(pLabel), I(i));
    }

    /**
     * Esse estilo é uma cor específica escolhida a mão conforme a consistência com a interface. O objetivo é
     * destacar o item com uma cor que permanecerá mesmo que outro item seja selecionado.
     * @return Estilo da Seleção
     */
    QString Style::itemSelectStyle() {
        return QString("QDialog {"
                       "    border: none;"
                       "    background-color: rgba(%1, %2, %3, %4);"
                       "    border-radius: 10px; "
                       "}").arg(I(90), I(70), I(160), I(150));
    }

    /**
     * Função para customizar o label usado para mostrar a capa ou os ícones de áudio ou vídeo
     * para os arquivos multimídia importados.
     * @return Estilo da Label
     */
    QString Style::labelPixmapStyle() {
        return QString("QLabel {"
                       "    border: 2px outset rgb(%2, %3, %4);"
                       "    background-color: rgba(0, 0, 0, %1);"
                       "    border-radius: 10px; "
                       "}").arg(I(pLabel), I(t.red()), I(t.green()), I(t.blue()));
    }

    /**
     * Estilo da lista de reprodução que irá exibir as mídias ou a lista importada.
     * @return Estilo da Playlist
     */
    QString Style::playlistStyle() {
        return QString("QListWidget {"
                       "    background-color: transparent;"
                       "}"
                       "QListWidget::item:selected {"
                       "    background-color: rgba(%1, %2, %3, %4);"
                       "    border-radius: 10px;"
                       "}").arg(I(m.red()), I(m.green()), I(m.blue()), I(pSelect));
    }

    /**
     * Retorna a margem padrão para o layout dos controles e playlist.
     * @return Margem principal
     */
    QMargins Style::marginStyle() {
        int i{settingsManager->programTheme() == QCineSettingsManager::Rounded ? roundMargin : defMargin};
        return {i, i, i, i};
    }

    /**
     * Retorna a margem padrão para o layout da playlist para o gradient.
     * @return Margem Auxiliar
     */
    QMargins Style::internalMarginStyle(Styles style) {
        int i{settingsManager->programTheme() == QCineSettingsManager::Gradient ? roundMargin : defMargin};
        int s{settingsManager->programTheme() == QCineSettingsManager::Gradient &&
              style == Styles::NoAjust ? roundMargin : defMargin};

        return {s, i, i, i};
    }

    /**
     * Retorna o espaço para o layout dos controles e playlist.
     * @return Espaço entre eles
     */
    int Style::spaceStyle() {
        if (settingsManager->programTheme() == QCineSettingsManager::Rounded)
            return roundMargin;

        if (settingsManager->programTheme() == QCineSettingsManager::Gradient)
            return gradientMargin;

        return defMargin;
    }

    /**
     * Espaçamento para o slider que mostra o progresso de reprodução.
     * @return Espaçamento Extra
     */
    QMargins Style::spaceSlider() {
        int i{settingsManager->programTheme() == QCineSettingsManager::Rounded ? spaceRoundSlider : defSpaceSlider};
        return {i, defMargin, i, defMargin};
    }

    /**
     * O tema padrão do programa vai ser o Breeze Dark e deu.
     * @return Paleta do Tema
     */
    QPalette Style::darkTheme() {
        QPalette darkTheme;

        QVariantList colors = {
                QVariant({QPalette::Window, QColor(42, 46, 50)}),
                QVariant({QPalette::WindowText, QColor(252, 252, 252)}),
                QVariant({QPalette::Base, QColor(27, 30, 32)}),
                QVariant({QPalette::AlternateBase, QColor(35, 38, 41)}),
                QVariant({QPalette::ToolTipBase, QColor(49, 54, 59)}),
                QVariant({QPalette::ToolTipText, QColor(252, 252, 252)}),
                QVariant({QPalette::PlaceholderText, QColor(252, 252, 252)}),
                QVariant({QPalette::Text, QColor(252, 252, 252)}),
                QVariant({QPalette::Button, QColor(49, 54, 59)}),
                QVariant({QPalette::ButtonText, QColor(252, 252, 252)}),
                QVariant({QPalette::BrightText, QColor(255, 255, 255)}),
                QVariant({QPalette::Light, QColor(64, 70, 76)}),
                QVariant({QPalette::Midlight, QColor(54, 59, 64)}),
                QVariant({QPalette::Dark, QColor(25, 27, 29)}),
                QVariant({QPalette::Mid, QColor(37, 41, 44)}),
                QVariant({QPalette::Shadow, QColor(18, 20, 21)}),
                QVariant({QPalette::Highlight, QColor(61, 174, 233)}),
                QVariant({QPalette::HighlightedText, QColor(252, 252, 252)}),
                QVariant({QPalette::Link, QColor(29, 153, 243)}),
                QVariant({QPalette::LinkVisited, QColor(155, 89, 182)})
        };

        foreach(auto t, colors)
            darkTheme.setColor(t.toList().at(0).value<QPalette::ColorRole>(), t.toList().at(1).value<QColor>());

        return darkTheme;
    }

} // QCineStyle