/**
 * Configurações do sistema, que terá todas as configurações do pragrama.
 */

#include "Settings.hpp"

namespace QCineSettings {

    Settings::Settings() {
        this->setStyleSheet(QCineStyle::Style().dialogStyle());
        this->setMinimumWidth(500);

        /** Debug e configuração */
        debug = new QCineDebug::Debug();
        settingsManager = new QCineSettingsManager::SettingsManager();
        auto theme = settingsManager->programTheme();
        auto bgtheme = settingsManager->programBackground();

        /** Variáveis de ambiente para o programa */
        auto env = new QCineEnvironmentVariable::EnvironmentVariable();
        connect(env, &QCineEnvironmentVariable::EnvironmentVariable::enterBox, this, &Settings::enterBox);

        /** Botão de fechar */
        auto *closeButton = new QCineButtons::Buttons(defIconSize, QCineIcon::Close);
        connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

        /** Layout do botão de fechar e título */
        auto clayout = new QHBoxLayout();
        clayout->addSpacing(5);
        clayout->addWidget(new QLabel("Settings"));
        clayout->addStretch(1);
        clayout->addWidget(closeButton);

        /** Layout para a seleção da cor do tema */
        auto *checkColor = new QHBoxLayout();
        checkColor->setContentsMargins(QMargins());

        QList<QCineStyle::ColorStyle> i = {QCineStyle::SystemColor, QCineStyle::Black};
        auto cr = (QCineStyle::ColorStyle)settingsManager->colorTheme();
        int n{1};

        /** Populando o layout com várias opções de cores */
        for (QCineStyle::ColorStyle c : i) {

            auto cl = new QRadioButton();
            cl->setFixedSize(defRadiusColor, defRadiusColor);
            cl->setStyleSheet(QCineStyle::Style().styleRadiusColor(c));
            cl->setProperty("id", n);
            connect(cl, &QRadioButton::toggled, [&, cl](bool checked){ changeColorTheme(checked, cl); });

            if ((QCineStyle::ColorStyle) cr == c)
                cl->setChecked(true);

            checkColor->addWidget(cl);
            n++;
        }

        includedef = new QCheckBox(tr("Include Default Background"));
        connect(includedef, &QCheckBox::stateChanged, this, &Settings::useDefaultBackground);

        if (settingsManager->useDefaultBackground() == checkTrue) includedef->setChecked(true);
        includedef->setVisible(bgtheme == QCineSettingsManager::Random);

        gradck = new QCheckBox(tr("Double Gradient Strength"));
        connect(gradck, &QCheckBox::stateChanged, [&](int i){ settingsManager->doubleGradient(i); });

        if (settingsManager->doubleGradient() == checkTrue) gradck->setChecked(true);
        gradck->setVisible(theme == QCineSettingsManager::Gradient);

        effectDisable = new QCheckBox(tr("Disable Effect"));
        connect(effectDisable, &QCheckBox::stateChanged, this, &Settings::changeEnableEffect);
        effectDisable->setChecked(settingsManager->statusEffect() == checkTrue);

        effectDisableBG = new QCheckBox(tr("Disable Background Effect"));
        connect(effectDisableBG, &QCheckBox::stateChanged, this, &Settings::changeEnableEffectBG);
        effectDisableBG->setChecked(settingsManager->statusEffectBackground() == checkTrue);

        /** Slider para selecionar a duração dos efeitos */
        auto effectduration = new QCineSettingsSlider::SettingsSlider(tr("Effect Duration"), "ms", 100);
        effectduration->setValues(effectTimeMin, effectTimeMax);
        effectduration->setValue(settingsManager->changeEffect());
        connect(effectduration, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeEffectDuration);

        /** Slider para selecionar a duração da transição do background */
        auto effectdurationbg = new QCineSettingsSlider::SettingsSlider(tr("Transition Duration"), "ms", 100);
        effectdurationbg->setValues(effectTimeMinBG, effectTimeMaxBG);
        effectdurationbg->setValue(settingsManager->changeEffectBackground());
        connect(effectdurationbg, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeEffectDurationBG);

        /** Slider para selecionar o tempo para ocultar os controles */
        auto effecthide = new QCineSettingsSlider::SettingsSlider(tr("Hide Time"), "ms", 100);
        effecthide->setValues(effControlHideMin, effControlHideMax);
        effecthide->setValue(settingsManager->effectHideTime());
        connect(effecthide, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeEffectTime);

        /** Slider para selecionar a transparência */
        auto transparency = new QCineSettingsSlider::SettingsSlider(tr("Opacity"), nullptr, 10, 5);
        transparency->setValues(defMinOpacity, defMaxOpacity);
        transparency->setValue(settingsManager->opacityTheme());
        connect(transparency, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeOpacityTheme);

        /** Slider para ajustar o desfoco */
        auto focus = new QCineSettingsSlider::SettingsSlider(tr("Blur"), nullptr, 10, 5);
        focus->setValues(defMinBlur, defMaxBlur);
        focus->setValue(settingsManager->blurBackground());
        connect(focus, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeBlurBackground);

        /** Slider para definir o tamanho da borda */
        borderSize = new QCineSettingsSlider::SettingsSlider(tr("Border Size"), "px", 0, 0, sliderBorderSize);
        borderSize->setValues(defMinBorder, defMaxBorder);
        borderSize->setValue(settingsManager->borderSize());
        borderSize->setVisible(theme > QCineSettingsManager::Default);
        connect(borderSize, &QCineSettingsSlider::SettingsSlider::valueChanged, this, &Settings::changeBorderTheme);

        /** Escolher o tema do programa */
        auto *comboBox = new QCineComboBox::ComboBox();
        comboBox->addItems(settingsManager->defProgramTheme());
        comboBox->setCurrentIndex(theme);
        connect(comboBox, &QCineComboBox::ComboBox::enterBox, this, &Settings::enterBox);
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                &QCineSettings::Settings::handleComboBoxChange);

        /** Selecionar o plano de fundo */
        auto *bgCombo = new QCineComboBox::ComboBox();
        bgCombo->addItems(settingsManager->defProgramBackground());
        bgCombo->setCurrentIndex(bgtheme);
        connect(bgCombo, &QCineComboBox::ComboBox::enterBox, this, &Settings::enterBox);
        connect(bgCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                &QCineSettings::Settings::handleComboBoxBg);

        /** Selecionar a ENGINE de reprodução multimídia */
        auto *engineCombo = new QCineComboBox::ComboBox();
        engineCombo->addItems(settingsManager->defProgramEngine());
        engineCombo->setCurrentIndex(
            settingsManager->videoEngine() > settingsManager->defProgramEngine().size() - 1 ? 0 :
            settingsManager->videoEngine()
        ); // Correção caso uma engine seja retirada

        connect(engineCombo, &QCineComboBox::ComboBox::enterBox, this, &Settings::enterBox);
        connect(engineCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                &QCineSettings::Settings::handleComboBoxEngine);

        /** Engine do programa */
        auto *enginebox = new QGroupBox(tr("Multimedia Engine"));
        auto *controlsEngine = new QGridLayout(enginebox);
        controlsEngine->addWidget(new QLabel(tr("Current Engine") + ":"), 0, 0);
        controlsEngine->addWidget(engineCombo, 0, 1);

        /** Tema do programa */
        auto *themebox = new QGroupBox(tr("Themes"));
        auto *controlsTheme = new QGridLayout(themebox);
        controlsTheme->addWidget(new QLabel(tr("Program Theme") + ":"), 0, 0);
        controlsTheme->addWidget(comboBox, 0, 1);
        controlsTheme->addLayout(checkColor, 0, 2);
        controlsTheme->addWidget(transparency, 1, 0, 1, 3);
        controlsTheme->addWidget(borderSize, 2, 0, 1, 3);
        controlsTheme->addWidget(gradck, 3, 0, 1, 3);

        /** Plano de fundo */
        auto *bgbox = new QGroupBox(tr("Background"));
        auto *bgTheme = new QGridLayout(bgbox);
        bgTheme->addWidget(new QLabel(tr("Background Theme") + ":"), 0, 0);
        bgTheme->addWidget(bgCombo, 0, 1);
        bgTheme->addWidget(focus, 1, 0, 1, 2);
        bgTheme->addWidget(includedef, 2, 0, 1, 2);

        /** Layout dos efeitos dos controles */
        auto *effcontrol = new QGroupBox(tr("Player Controls"));
        auto *controllayout = new QVBoxLayout(effcontrol);
        controllayout->addWidget(effecthide);

        /** Layout dos efeitos */
        auto *effectgroup = new QGroupBox(tr("Transition Effects"));
        auto *pllayout = new QVBoxLayout(effectgroup);
        pllayout->addWidget(effectduration);
        pllayout->addWidget(effectDisable);

        /** Efeitos do background */
        auto *effectbg = new QGroupBox(tr("Background Effects"));
        auto bglayout = new QVBoxLayout(effectbg);
        bglayout->addWidget(effectdurationbg);
        bglayout->addWidget(effectDisableBG);

        /** Aba de customização */
        auto *custom = new QWidget();
        auto *customBox = new QVBoxLayout(custom);
        customBox->addWidget(themebox);
        customBox->addWidget(bgbox);
        customBox->addStretch(1);

        /** Aba de efeitos */
        auto *effect = new QWidget();
        auto *effectBox = new QVBoxLayout(effect);
        effectBox->addWidget(effectgroup);
        effectBox->addWidget(effcontrol);
        effectBox->addWidget(effectbg);
        effectBox->addStretch(1);

        /** Aba de performance */
        auto *performance = new QWidget();
        auto *performanceBox = new QVBoxLayout(performance);
        performanceBox->addWidget(enginebox);
        performanceBox->addStretch(1);

        /** Layout principal */
        auto *layout = new QVBoxLayout(this);
        auto *tabWidget = new QTabWidget(this);
        //tabWidget->addTab(new QWidget(), tr("General")); //todo
        tabWidget->addTab(custom, tr("Custom"));
        tabWidget->addTab(effect, tr("Effects"));
        tabWidget->addTab(performance, tr("Performance"));
        tabWidget->addTab(env, tr("Environment Variables"));
        layout->addLayout(clayout);
        layout->addWidget(tabWidget);
    }

    /**
     * Função para setar a opacidade do tema do programa.
     * @param i - Valor para a opacidade.
     */
    void Settings::changeOpacityTheme(int i) {
        settingsManager->opacityTheme(i);
        Q_EMIT changeOpacity();
    }

    /**
     * Função para escolher o tema do programa.
     * @param i - Valor numérico para selecionar o tema.
     */
    void Settings::handleComboBoxChange(int i) {
        borderSize->setVisible((QCineSettingsManager::Theme)i > QCineSettingsManager::Default);
        gradck->setVisible((QCineSettingsManager::Theme)i == QCineSettingsManager::Gradient);
        settingsManager->programTheme(i);
        Q_EMIT changeTheme();
    }

    /**
     * Função para escolher as configurações de background do programa.
     * @param i - Valor numérico para selecionar o tema.
     */
    void Settings::handleComboBoxBg(int i) {
        includedef->setVisible((QCineSettingsManager::Theme)i == QCineSettingsManager::Random);
        settingsManager->programBackground(i);
        Q_EMIT changeBackground();
    }

    /**
     * Função para o desfoque do plano de fundo do programa.
     * @param i - Valor para o desfoco.
     */
    void Settings::changeBlurBackground(int i) {
        settingsManager->blurBackground(i);
        Q_EMIT changeBlur();
    }

    /**
     * Função para escolher as configurações de engine do programa.
     * @param i - Valor numérico para selecionar a engine.
     */
    void Settings::handleComboBoxEngine(int i) {
        settingsManager->videoEngine(i);
        Q_EMIT changeEngine();
    }

    /**
     * Definindo o tamanho da margem dos controles e playlist.
     * @param i - Valor para definir o tamanho.
     */
    void Settings::changeBorderTheme(int i) {
        settingsManager->borderSize(i);
        Q_EMIT changeOpacity();
    }

    /**
     * Ativando ou desativando os efeitos dos controles e playlist.
     * @param i - Valor para alteração.
     */
    void Settings::changeEnableEffect(int i) {
        settingsManager->statusEffect(i);
        Q_EMIT disableEffect(i == checkTrue);
    }

    /**
     * Ativando ou desativando os efeitos de transição do plano de fundo do programa.
     * @param i - Valor para alteração.
     */
    void Settings::changeEnableEffectBG(int i) {
        settingsManager->statusEffectBackground(i);
        Q_EMIT disableEffectBG(i == checkTrue);
    }

    /**
     * Ativando ou desativando os efeitos de transição do plano de fundo do programa.
     * @param i - Valor para alteração.
     */
    void Settings::useDefaultBackground(int i) {
        settingsManager->useDefaultBackground(i);
    }

    /**
     * Alterando a duração dos efeitos de exibição e ocultação dos controles e playlist.
     * @param i - Valor para a definição.
     */
    void Settings::changeEffectDuration(int i) {
        settingsManager->changeEffect(i);
        Q_EMIT changeEffect(i);

        if (settingsManager->statusEffect() == checkTrue) {
            settingsManager->statusEffect(0);
            effectDisable->setChecked(false);
        }
    }

    /**
     * Alterando a tempo de exibição dos controles multimídia.
     * @param i - Valor para a definição.
     */
    void Settings::changeEffectTime(int i) {
        settingsManager->effectHideTime(i);
        Q_EMIT changeHideEffect(i);
    }

    /**
     * Alterando a duração dos efeitos de transição do plano de fundo do programa.
     * @param i - Valor para a definição.
     */
    void Settings::changeEffectDurationBG(int i) {
        settingsManager->changeEffectBackground(i);
        Q_EMIT changeEffectBG(i);

        if (settingsManager->statusEffectBackground() == checkTrue) {
            settingsManager->statusEffectBackground(0);
            effectDisableBG->setChecked(false);
        }
    }

    /**
     * Alterando o plano de fundo dos controles e playlist.
     * @param button - Botão para identificação.
     */
    void Settings::changeColorTheme(bool checked, QRadioButton *button) {
        if (!checked)
            return;

        int id = button->property("id").toInt();
        if (id == 1) {
            debug->msg("Plano de fundo padrão para os controles e playlist", "Settings");
            settingsManager->colorTheme(QCineStyle::SystemColor);
        } else if (id == 2) {
            debug->msg("Plano de fundo preto para os controles e playlist", "Settings");
            settingsManager->colorTheme(QCineStyle::Black);
        }
        Q_EMIT changeOpacity();
    }

    void Settings::showEvent(QShowEvent *event) {
        Q_EMIT dialogShow(true);
        QDialog::showEvent(event);
    }

    void Settings::hideEvent(QHideEvent *event) {
        Q_EMIT dialogShow(false);
        QDialog::hideEvent(event);
    }

    void Settings::enterEvent(QEnterEvent *event) {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        Q_EMIT dialogShow(true);
        QDialog::enterEvent(event);
    }

} // QCineSettings