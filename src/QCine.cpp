/**
 * Interface principal do programa.
 * É onde será desenhado o layout principal do programa.
 */

#include "QCine.hpp"

namespace QCine {

# define title "QCine Multimedia Player"

    QCine::QCine() {
        this->setWindowTitle(title);
        this->setWindowIcon(QIcon(QCineDefaultPath::DefaultPath().defalutPath(defIcon)));

        /** Debug, background e configurações */
        debug = new QCineDebug::Debug();
        background = new QCineBackground::Background();
        settingsManager = new QCineSettingsManager::SettingsManager(this);

        /** Efeitos para o controle de multimídia */
        auto *widgetsControl = new QWidget();
        widgetsControl->setMouseTracking(true);
        effects = new QCineEffects::Effects(widgetsControl);

        /** Mapeador de clique */
        clickMapper = new QCineClickMapper::ClickMapper();
        connect(clickMapper, &QCineClickMapper::ClickMapper::singleClick, this, &QCine::changePlayPause);
        connect(clickMapper, &QCineClickMapper::ClickMapper::doubleClick, this, &QCine::changeFullscreen);

        /** Temporizador para checar o mouse */
        checkMouse = new QCineCheckMouse::CheckMouse();
        connect(checkMouse, &QCineCheckMouse::CheckMouse::movingMouse, effects, &QCineEffects::Effects::showEffect);

        /** Controles de multimídia */
        controls = new QCineControls::Controls();
        widgetsControl->setFixedHeight(controls->height());
        connect(controls, &QCineControls::Controls::noEffect, this, &QCine::changeControls);
        connect(controls, &QCineControls::Controls::pressPlay, this, &QCine::changePlayPause);
        connect(controls, &QCineControls::Controls::pressStop, this, &QCine::stop);
        connect(controls, &QCineControls::Controls::pressNext, this, &QCine::next);
        connect(controls, &QCineControls::Controls::pressPrevious, this, &QCine::previous);

        /** Reprodutor multimídia */
        player = new QCinePlayer::Player();
        connect(player, &QCinePlayer::Player::checkVideo, this, &QCine::changeStack);
        connect(player, &QCinePlayer::Player::endMedia, this, &QCine::changeEndMedia);
        connect(player, &QCinePlayer::Player::durationChange, controls, &QCineControls::Controls::sliderDuration);
        connect(player, &QCinePlayer::Player::positionChange, controls, &QCineControls::Controls::sliderPosition);
        connect(controls, &QCineControls::Controls::valueChanged, player, &QCinePlayer::Player::setPosition);

        /** Diálogo de configurações */
        settings = new QCineSettings::Settings();
        connect(settings, &QCineSettings::Settings::changeTheme, this, &QCine::changeTheme);
        connect(settings, &QCineSettings::Settings::changeOpacity, this, &QCine::changeOpacity);
        connect(settings, &QCineSettings::Settings::changeBlur, this, &QCine::changeBlur);
        connect(settings, &QCineSettings::Settings::enterBox, this, &QCine::statusComboBox);
        connect(settings, &QCineSettings::Settings::changeEngine, this, &QCine::changeEngine);
        connect(settings, &QCineSettings::Settings::disableEffect, effects, &QCineEffects::Effects::setDisableEffect);
        connect(settings, &QCineSettings::Settings::changeEffect, effects, &QCineEffects::Effects::changeEffectDuration);
        connect(settings, &QCineSettings::Settings::disableEffectBG, background, &QCineBackground::Background::disableAnimation);
        connect(settings, &QCineSettings::Settings::changeEffectBG, background, &QCineBackground::Background::transitionDuration);
        connect(settings, &QCineSettings::Settings::changeHideEffect, checkMouse, &QCineCheckMouse::CheckMouse::setHideTimer);
        connect(settings, &QCineSettings::Settings::dialogShow,this, &QCine::changeSettings);
        connect(settings, &QCineSettings::Settings::changeBackground, [&]() { background->changeBackground(); });

        /** Playlist do programa */
        playlist = new QCinePlaylist::Playlist();
        connect(playlist, &QCinePlaylist::Playlist::isFirstPlay, this, &QCine::firstPlay);
        connect(playlist, &QCinePlaylist::Playlist::noEffect, this, &QCine::changeplaylist);
        connect(playlist, &QCinePlaylist::Playlist::enterBox, this, &QCine::statusComboBox);
        connect(playlist, &QCinePlaylist::Playlist::dialogShow, this, &QCine::changeFileDialog);
        connect(playlist, &QCinePlaylist::Playlist::finish, [&](){ clickMapper->isBlockClick(false); });

        /** Ajustes da playlist */
        auto wPlaylist = new QWidget();
        spPlaylist = new QVBoxLayout(wPlaylist);
        spPlaylist->setContentsMargins(QCineStyle::Style().internalMarginStyle());
        spPlaylist->addWidget(playlist);

        /** Playlist redimensionável */
        auto sparcer = new QWidget();
        sparcer->setMouseTracking(true);
        sparcer->installEventFilter(this);
        splitter = new QSplitter(Qt::Horizontal);
        splitter->setMouseTracking(true);
        splitter->addWidget(sparcer);
        splitter->addWidget(wPlaylist);
        splitter->setSizes(settingsManager->splitterSizes());
        splitter->setCollapsible(splitter->indexOf(wPlaylist), false);
        splitter->setStyleSheet("QSplitter::handle { background-color: transparent; }");
        splitter->handle(1)->installEventFilter(this);

        /** Efeito do splitter */
        effectp = new QCineEffects::Effects(splitter);
        connect(settings, &QCineSettings::Settings::disableEffect, effectp, &QCineEffects::Effects::setDisableEffect);
        connect(settings, &QCineSettings::Settings::changeEffect, effectp, &QCineEffects::Effects::changeEffectDuration);

        /** Layout intermediário para facilitar o mapeamento do mouse e os efeitos */
        auto *wcontrols = new QVBoxLayout(widgetsControl);
        wcontrols->setContentsMargins(QMargins());
        wcontrols->addWidget(controls);

        /** Controles flutuantes */
        floatWidget = new QCineFloatWidget::FloatWidget(this);
        floatWidget->resize(this->size());
        floatWidget->move(this->pos());
        connect(floatWidget, &QCineFloatWidget::FloatWidget::contextMenu, this, &QCine::contextMenu);
        connect(floatWidget, &QCineFloatWidget::FloatWidget::leave, this, &QCine::changeLeave);
        connect(floatWidget, &QCineFloatWidget::FloatWidget::release, clickMapper, &QCineClickMapper::ClickMapper::mapClicks);
        connect(floatWidget, &QCineFloatWidget::FloatWidget::mousePos, checkMouse, &QCineCheckMouse::CheckMouse::mousePos);

        /** Layout Horizontal das configurações */
        auto hsettings = new QHBoxLayout();
        hsettings->setContentsMargins(QMargins());
        hsettings->addWidget(settings);
        hsettings->addStretch(1);

        /** Layout Vertical das configurações */
        lsettings = new QVBoxLayout();
        lsettings->setContentsMargins(QCineStyle::Style().internalMarginStyle(QCineStyle::NoAjust));
        lsettings->addLayout(hsettings);
        lsettings->addStretch(1);

        /** Widgets enfileirados */
        stackedWidget = new QStackedWidget();
        stackedWidget->addWidget(background);
        stackedWidget->addWidget(player->widget());

        /** Layout para sobreposição de outros widgets */
        auto hbox = new QGridLayout();
        hbox->setContentsMargins(QMargins());
        hbox->addWidget(splitter, 0, 0);
        hbox->addLayout(lsettings, 0, 0);

        /** Layout para a playlist e os controles */
        allcontrols = new QVBoxLayout(floatWidget);
        allcontrols->setContentsMargins(QCineStyle::Style().marginStyle());
        allcontrols->setSpacing(QCineStyle::Style().spaceStyle());
        allcontrols->addLayout(hbox);
        allcontrols->addWidget(widgetsControl);

        /** Layout principal, this ao invés de setLayout */
        auto *mainlayout = new QVBoxLayout(this);
        mainlayout->setContentsMargins(QMargins());
        mainlayout->addWidget(stackedWidget);

        /** Teclas de atalho */
        auto *shortcut = new QShortcut(QKeySequence(Qt::AltModifier | Qt::Key_S), this);
        connect(shortcut, &QShortcut::activated, settings, &QCineSettings::Settings::show);
        auto *shortcut2 = new QShortcut(QKeySequence(Qt::ControlModifier | Qt::Key_O), this);
        connect(shortcut2, &QShortcut::activated, [&](){ playlist->addFiles(); });

        floatWidget->show();
        settings->close();
    }

    /**
     * Executar o primeiro arquivo multimídia adicionado.
     * @param file - Arquivo multimídia.
     */
    void QCine::firstPlay(const QString &file) {
        if (player->isPlaying())
            return;

        play(file);
    }

    /**
     * Reproduzindo arquivos multimídia e executar ações ao reproduzir.
     * @param file - Arquivo multimídia.
     */
    void QCine::play(const QString &file) {
        player->play(file);
        controls->playBtn()->btn(QCineIcon::Pause);
        controls->sliderEnabled(true);
        this->setWindowTitle(player->currentMedia());
    }

    /**
     * Reproduzindo e pausando o reprodutor multimídia, já fazendo o
     * ajuste do botão play/pause.
     */
    void QCine::changePlayPause() {
        if (!player->isMedia())
            return;

        if (player->isPlaying() && !player->isPausing()) {
            player->pause();
            controls->playBtn()->btn(QCineIcon::Play);
            return;
        }

        play();
    }

    /**
     * Parando a reprodução de arquivos multimídia.
     */
    void QCine::stop() {
        if (player->isPlaying()) {
            player->stop();
            stackedWidget->setCurrentWidget(background);
        }
        controls->playBtn()->btn(QCineIcon::Play);
        controls->sliderPosition(0);
        controls->sliderEnabled(false);
        this->setWindowTitle(title);
    }

    /**
     * Pulando para a próxima mídia.
     */
    void QCine::next() {
        if (!player->isPlaying())
            return;

        play(playlist->model()->indexOfNext(player->currentMedia()));
    }

    /**
     * Pulando para a mídia anterior.
     */
    void QCine::previous() {
        if (!player->isPlaying())
            return;

        play(playlist->model()->indexOfPrevious(player->currentMedia()));
    }

    /**
     * Controle de quando a mídia termina para acessar a próxima mídia da playlist ou parar a reprodução.
     */
    void QCine::changeEndMedia() {
        auto model = playlist->model();

        if (model->indexOf(player->currentMedia()) == model->countIndex()) {
            stop();
            player->setCurrentMedia(playlist->model()->indexOfNext(player->currentMedia()));
        }
        next();
    }

    /**
     * Verificação de execução de vídeos ou áudios.
     * @param b - Valor booleano para indicação.
     */
    void QCine::changeStack(bool b) {
        if (b) {
            debug->msg("Setando o player de vídeo", "QCine");
            stackedWidget->setCurrentWidget(player->widget());
        } else {
            debug->msg("Setando o visualizador de plano de fundo", "QCine");
            stackedWidget->setCurrentWidget(background);
        }
    }

    /**
     * Ações para as emissões dos controles.
     * @param b - Valor booleano.
     */
    void QCine::changeControls(bool b) {
        QApplication::restoreOverrideCursor(); // Controle de erro
        if (isNoLeave())
            return;

        checkMouse->noMouseCheck(b);
        clickMapper->isBlockClick(b);

        if (effectp->isShow())
            effectp->showEffect(false);

        isSplit(false); // Controle de Erro
        isControlShow(b);

        /** Correção de bug */
        if (!effects->isShow()) {
            checkMouse->isAlready(true);
            effects->showEffect(true);
        }
    }

    /**
     * Ações para as emissões da Playlist.
     * @param b - Valor booleano.
     */
    void QCine::changeplaylist(bool b) {
        QApplication::restoreOverrideCursor(); // Controle de erro
        if (isNoLeave())
            return;

        if (!b && isSplit()) {
            isSplit(false);
        } else {
            checkMouse->noMouseCheck(b);
            clickMapper->isBlockClick(b);
        }

        if (!effectp->isShow())
            effectp->showEffect(b);

        isSplit(false); // Controle de Erro

        /** Correção de bug */
        if (!effects->isShow()) {
            checkMouse->isAlready(true);
            effects->showEffect(true);
        }
    }

    /**
     * Ações para as emissões do diálogo de configurações.
     * @param b - Valor booleano.
     */
    void QCine::changeSettings(bool b) {
        checkMouse->isDialog(b);
        clickMapper->isBlockClick(b);
    }

    /**
     * Ações ao abrir o fileDialog na playlist.
     * @param b - Valor booleano.
     */
    void QCine::changeFileDialog(bool b) {
        checkMouse->isContextMenu(b);

        if (b)
            floatWidget->hide();
        else
            floatWidget->show();
    }

    /**
     * Necessário para bloquer o leaveEvent ao abrir o QListView personalizado, que é criado de forma flutuante.
     * por conta disso, o leaveEvent é disparado de forma indesejada gerando um bugs que precisam ser tratados.
     * @param b - Valor booleano.
     */
    void QCine::statusComboBox(bool b) {
        isNoLeave(b);
        if (!b) {
            auto m = this->mapFromGlobal(QCursor::pos());
            auto p = this->size();
            if (m.x() < 0 || m.y() < 0 || m.x() > p.width() || m.y() > p.height())
                floatWidget->hide();
        }
    }

    /**
     * Alternado a engine de reprodução do Programa.
     */
    void QCine::changeEngine() {
        stackedWidget->removeWidget(player->widget());
        player->changeEngine();
        stackedWidget->addWidget(player->widget());
        controls->playBtn()->btn(QCineIcon::Play);
        controls->sliderEnabled(false);
    }

    /**
     * Alterando o tema do programa. Vários elementos precisam ser reajustados
     * após escolher o novo estilo para o programa.
     */
    void QCine::changeTheme() {
        QCineStyle::Style s;

        lsettings->setContentsMargins(s.internalMarginStyle(QCineStyle::NoAjust));
        spPlaylist->setContentsMargins(s.internalMarginStyle());
        allcontrols->setContentsMargins(s.marginStyle());
        allcontrols->setSpacing(s.spaceStyle());
        controls->setStyleSheet(s.widgetStyle(QCineStyle::Controls));
        playlist->setStyleSheet(s.widgetStyle(QCineStyle::Playlist));
        settings->setStyleSheet(s.dialogStyle());
        menu->setStyleSheet(s.contextMenuStyle());
        controls->sliderLayout()->setContentsMargins(s.spaceSlider());
    }

    /**
     * Alterando o tema para alterar o estilo do programa.
     */
    void QCine::changeOpacity() {
        QCineStyle::Style s;

        controls->setStyleSheet(s.widgetStyle(QCineStyle::Controls));
        playlist->setStyleSheet(s.widgetStyle(QCineStyle::Playlist));
        settings->setStyleSheet(s.dialogStyle());
        menu->setStyleSheet(s.contextMenuStyle());
    }

    /**
     * Função para alterar o modo tela cheia do programa.
     */
    void QCine::changeFullscreen() {
        if (this->isFullScreen()) {
            if (settingsManager->windowMaximize()) this->showMaximized();
            else this->showNormal();
        } else {
            this->showFullScreen();
        }
    }

    /**
     * Ação a ser executada quando o mouse sair sobre o programa.
     */
    void QCine::changeLeave() {
        if (isNoLeave())
            return;

        if (effectp->isShow()) {
            effectp->showEffect(false); // Ocultar Playlist
            checkMouse->hideEffect();      // Ocultar Controles
        }

        floatWidget->hide();
    }

    /**
     * Menu de contexto do programa.
     * @param point - Posição do menu.
     */
    void QCine::contextMenu(QPoint point) {
        QApplication::restoreOverrideCursor(); // Controle de erro

        if (effectp->isShow())
            return;

        if (isControlShow())
            return;

        menu = new QMenu();
        menu->setWindowFlag(Qt::FramelessWindowHint, true);
        menu->setAttribute(Qt::WA_TranslucentBackground, true);
        menu->setStyleSheet(QCineStyle::Style().contextMenuStyle());
        connect(menu, &QMenu::aboutToShow, [&](){ checkMouse->isContextMenu(true); });
        connect(menu, &QMenu::aboutToHide, [&](){ checkMouse->isContextMenu(false); });

        /** Adicionar arquivos */
        QAction *actFiles = menu->addAction(tr("Open Files"));
        actFiles->setShortcut(QKeySequence(Qt::ControlModifier | Qt::Key_O));
        actFiles->setIcon(QCineIcon::Icon(64, 0).setIcon(QCineIcon::AddMenu));
        connect(actFiles, &QAction::triggered, [&]() { playlist->addFiles(); });

        /** Configurações */
        QAction *actSettings = menu->addAction(tr("Settings"));
        actSettings->setShortcut(QKeySequence(Qt::AltModifier | Qt::Key_S));
        actSettings->setIcon(QCineIcon::Icon(64, 0).setIcon(QCineIcon::Settings));
        connect(actSettings, &QAction::triggered, settings, &QCineSettings::Settings::show);

        menu->exec(point);
    }

    /**
     * Funções Protegidas
     ******************************************************************************************************************/

    void QCine::changeEvent(QEvent *event) {
        if (event->type() == QEvent::ActivationChange) {
            if (this->isActiveWindow()) {
                debug->msg("Janela Ativa", "QCine");
            } else {
                debug->msg("Janela Inativa", "QCine");
            }
        }

        if (event->type() == QEvent::WindowStateChange) {
            switch (this->windowState()) {
                case Qt::WindowNoState:
                    debug->msg("Restaurando janela do programa", "QCine");
                    settingsManager->windowMaximize(false);
                    break;
                case Qt::WindowMinimized:
                    debug->msg("Minimizando janela do programa", "QCine");
                    break;
                case Qt::WindowMaximized:
                    debug->msg("Maximizando janela do programa", "QCine");

                    if (isMinimizeMaximized()) {
                        isMinimizeMaximized(false); // Controle de erro
                        break;
                    }

                    settingsManager->windowGeometry(this->geometry()); // Tem que salvar antes
                    settingsManager->windowMaximize(true);
                    break;
                case (Qt::WindowMinimized | Qt::WindowMaximized):
                    debug->msg("Minimizando janela maximizada do programa", "QCine");
                    isMinimizeMaximized(true);
                    break;
            }
        }
        QWidget::changeEvent(event);
    }

    void QCine::closeEvent(QCloseEvent *event) {
        debug->msg("Fechando o programa", "QCine");
        stop();

        if (!this->isMaximized()) // Se tiver maximizado dá zica
            settingsManager->windowGeometry(this->geometry());

        settingsManager->splitterSizes(splitter->sizes());
        QWidget::closeEvent(event);
    }

    void QCine::enterEvent(QEnterEvent *event) {
        floatWidget->show();
        QWidget::enterEvent(event);
    }

    void QCine::moveEvent(QMoveEvent *event) {
        floatWidget->move(event->pos());
        QWidget::moveEvent(event);
    }

    void QCine::resizeEvent(QResizeEvent *event) {
        floatWidget->resize(event->size());
        QWidget::resizeEvent(event);
    }

    /**
     * Tudo isso aqui é pra correção de bugs da interface relacionado aos eventos do mouse.
     * É um filtro de eventos para o espaçamento da playlist e o handle do qsplitter.
     */
    bool QCine::eventFilter(QObject *obj, QEvent *event) {
        if (dynamic_cast<QSplitterHandle*>(obj) && event->type() == QEvent::Enter) { // handle so QSplitter
            isSplit(true);
            checkMouse->noMouseCheck(true);

            if (!effectp->isShow())
                effectp->showEffect(true);

        } else if (dynamic_cast<QWidget*>(obj) && event->type() == QEvent::Enter) { // Widget de Espaçamento
            checkMouse->noMouseCheck(false);
            clickMapper->isBlockClick(false);

            if (effectp->isShow())
                effectp->showEffect(false);

            isSplit(false);
        }
        return QObject::eventFilter(obj, event);
    }

} // QCine
