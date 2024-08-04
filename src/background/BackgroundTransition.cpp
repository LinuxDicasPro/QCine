/**
 * Classe para os efeitos de transição do background do programa.
 * O processo completo de animação do background vai ocorrer aqui.
 */

#include "BackgroundTransition.hpp"

namespace QCineBackgroundTransition {

    BackgroundTransition::BackgroundTransition(bool noBlur,
                                               QSize screenSize,
                                               const QString &str) :screenSize(screenSize) {
        /** Definições */
        this->setRenderHint(QPainter::Antialiasing);
        this->setRenderHint(QPainter::SmoothPixmapTransform);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setResizeAnchor(AnchorViewCenter);
        this->setMouseTracking(true);
        this->setInteractive(true);
        this->setStyleSheet("background-color: transparent;");
        this->setFrameStyle(QFrame::NoFrame);

        /** Configurações e debug */
        debug = new QCineDebug::Debug();
        defaultPath = new QCineDefaultPath::DefaultPath();
        settingsManager = new QCineSettingsManager::SettingsManager();

        /** Desfoco para a classe */
        if (!noBlur) {
            blurEffect = new QGraphicsBlurEffect();
            blurEffect->setBlurRadius(settingsManager->blurBackground());
            viewport()->setGraphicsEffect(blurEffect);
        }

        /** Opacidade para os efeitos */
        opacityEffect = new QGraphicsOpacityEffect();
        opacityEffect->setOpacity(0);

        /** Itens para adicionar as imagens */
        item1 = new QGraphicsPixmapItem();
        item1->setTransformationMode(Qt::SmoothTransformation);
        item2 = new QGraphicsPixmapItem();
        item2->setTransformationMode(Qt::SmoothTransformation);
        item2->setGraphicsEffect(opacityEffect);

        /** Cena para os itens */
        scene = new QGraphicsScene();
        scene->addItem(item1);
        scene->addItem(item2);
        this->setScene(scene);

        /** Setando imagem ao iniciar o construtor */
        if (!str.isEmpty())
            itemPixmap(pixmap1, item1, false, str);
        else
            itemPixmap(pixmap1, item1, settingsManager->programBackground() == QCineSettingsManager::Random);

        /** Animação para o efeito */
        animation = new QPropertyAnimation(opacityEffect, "opacity");
        animation->setStartValue(0);
        animation->setEndValue(1);

        animation->setDuration(
                settingsManager->statusEffectBackground() ? 0 : settingsManager->changeEffectBackground()
        );

        connect(animation, &QPropertyAnimation::finished, this, &BackgroundTransition::effectEnd);
        connect(animation, &QPropertyAnimation::valueChanged, this, &BackgroundTransition::effectChanged);
    }

    /**
     * Alterando o background do programa.
     * @param str - Plano de fundo personalizado a ser definido. Pode vir de capas de áudio.
     */
    void BackgroundTransition::changeBackground(const QString &str) {
        (void) str; // todo

        if (isTransition()) {
            if (settingsManager->programBackground() == QCineSettingsManager::Random)
                itemPixmap(nextPixmap, nullptr, true);
            else
                itemPixmap(nextPixmap);

            isNextPixmap(true);
            return;
        }

        itemPixmap(pixmap2, item2, settingsManager->programBackground() == QCineSettingsManager::Random);
        animation->start();
    }

    /**
     * Função principal para alterar as imagens para a exibição e transição.
     * @param pixmap - O pixmap que vai armazenar a imagem.
     * @param item - O item pra setar o pixmaps.
     * @param random - Opcional, para setar números aleatórios.
     */
    void BackgroundTransition::itemPixmap(QPixmap &pixmap, QGraphicsPixmapItem *item, bool random, const QString &str) {
        if (str.isEmpty()) {
            int i{settingsManager->useDefaultBackground() == checkTrue ? 0 : 1};
            int n{random ? QRandomGenerator::global()->bounded(i, defaultPath->countFiles("background")) : 0};

            pixmap = QPixmap(defaultPath->defalutPath(QString("background/bg%1.png").arg(n))).scaled(
                    screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        } else {
            pixmap = QPixmap(defaultPath->defalutPath(str)).scaled(
                    screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        }

        if (item)
            item->setPixmap(pixmap);
    }

    /**
     * Ajustes para sinalizar que a animação está em execução.
     */
    void BackgroundTransition::effectChanged() {
        if (animation->state() == QAbstractAnimation::Stopped)
            return; // Controle de erro;

        if (!isTransition()) {
            isTransition(true);
            debug->msg("Plano de fundo em transição", "BackgroundTransition");
        }
    }

    /**
     * Ajustes para o próximo efeito ao finalizar a animação.
     */
    void BackgroundTransition::effectEnd() {
        item1->setPixmap(pixmap2);
        opacityEffect->setOpacity(0);
        isTransition(false);
        debug->msg("Plano de fundo alterado", "BackgroundTransition");

        if (isNextPixmap()) {
            pixmap2 = nextPixmap;
            item2->setPixmap(pixmap2);
            isNextPixmap(false);
            animation->start();
        }
    }

    void BackgroundTransition::wheelEvent(QWheelEvent *event) {
        event->ignore(); // ignorando rolagem do mouse
    }

    void BackgroundTransition::keyPressEvent(QKeyEvent *event) {
        event->ignore(); // tem que ignorar as teclas também
    }

} // QCineBackground
