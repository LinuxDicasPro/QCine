/**
 * Classe para o QSettings para centralizar as configurações em um lugar só.
 * Eu não vou comentar as funções porque até uma criança entende.
 */

#include "SettingsManager.hpp"

namespace QCineSettingsManager {

#define defaultOpacity 255
#define defaultBlur 150
#define defaultEffectTime 500
#define defaultEffectTimeBG 2000
#define defaultHideTime 2000

    SettingsManager::SettingsManager(QWidget *window) : win(window) {
        if (win) {
            QCineDebug::Debug().msg(
                    "Resolução da tela primária",
                    "SettingsManager",
                    {QString("%1x%2").arg(QString::number(rect.width()), QString::number(rect.height()))}
            );

            win->setMinimumSize(minSize());
            win->setGeometry(windowGeometry());
        }
    }

    void SettingsManager::windowMaximize(bool b) {
        this->setValue("WindowMaximize", b);
    }

    bool SettingsManager::windowMaximize() {
        return this->value("WindowMaximize", false).toBool();
    }

    void SettingsManager::windowGeometry(QRect rec) {
        this->setValue("WindowGeometry", rec);
    }

    QRect SettingsManager::windowGeometry() {
        return this->value("WindowGeometry",QRect(center().x(),center().y(),
                                                  minSize().width(),minSize().height())).toRect();
    }

    void SettingsManager::splitterSizes(const QList<int> &list) {
        this->setValue("splitterSizes", QList<QVariant>({list.at(0), list.at(1)}));
    }

    QList<int> SettingsManager::splitterSizes() {
        auto s = this->value("splitterSizes", QList<QVariant>({rect.width(), playlistMinWidth})).toList();
        return QList<int>({s.at(0).toInt(), s.at(1).toInt()});
    }

    void SettingsManager::programTheme(int i) {
        this->setValue("programTheme", i);
    }

    int SettingsManager::programTheme() {
        return this->value("programTheme", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::programBackground(int i) {
        this->setValue("programBackground", i);
    }

    int SettingsManager::programBackground() {
        return this->value("programBackground", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::opacityTheme(int i) {
        this->setValue("opacityTheme", i);
    }

    int SettingsManager::opacityTheme() {
        return this->value("opacityTheme", defaultOpacity).toInt();
    }

    void SettingsManager::blurBackground(int i) {
        this->setValue("blurBackground", i);
    }

    int SettingsManager::blurBackground() {
        return this->value("blurBackground", defaultBlur).toInt();
    }

    void SettingsManager::videoEngine(int i) {
        this->setValue("videoEngine", i);
    }

    int SettingsManager::videoEngine() {
        return this->value("videoEngine", QCineSettingsManager::UseQMediaPlayer).toInt();
    }

    void SettingsManager::borderSize(int i) {
        this->setValue("borderSize", i);
    }

    int SettingsManager::borderSize() {
        return this->value("borderSize", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::colorTheme(int i) {
        this->setValue("colorTheme", i);
    }

    int SettingsManager::colorTheme() {
        return this->value("colorTheme", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::doubleGradient(int i) {
        this->setValue("doubleGradient", i);
    }

    int SettingsManager::doubleGradient() {
        return this->value("doubleGradient", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::changeEffect(int i) {
        this->setValue("changeEffect", i);
    }

    int SettingsManager::changeEffect() {
        return this->value("changeEffect", defaultEffectTime).toInt();
    }

    void SettingsManager::changeEffectBackground(int i) {
        this->setValue("changeEffectBackground", i);
    }

    int SettingsManager::changeEffectBackground() {
        return this->value("changeEffectBackground", defaultEffectTimeBG).toInt();
    }

    void SettingsManager::statusEffect(int i) {
        this->setValue("statusEffect", i);
    }

    int SettingsManager::statusEffect() {
        return this->value("statusEffect", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::statusEffectBackground(int i) {
        this->setValue("statusEffectBackground", i);
    }

    int SettingsManager::statusEffectBackground() {
        return this->value("statusEffectBackground", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::useDefaultBackground(int i) {
        this->setValue("useDefaultBackground", i);
    }

    int SettingsManager::useDefaultBackground() {
        return this->value("useDefaultBackground", QCineSettingsManager::Default).toInt();
    }

    void SettingsManager::effectHideTime(int i) {
        this->setValue("controlHideTime", i);
    }

    int SettingsManager::effectHideTime() {
        return this->value("controlHideTime", defaultHideTime).toInt();
    }

} // QCineSettingsManager