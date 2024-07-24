/**
 * Classe para lidar com as variáveis de ambiente que serão carregados apenas na inicialização
 * do programa para garantir que as otimizações sejam efetivas.
 */

#include "EnvironmentVariable.hpp"

namespace QCineEnvironmentVariable {

#define spSize 10
#define ajustScroolWidth 20
#define defScroolHeight 210
#define checkTrue 2
#define checkFalse 0

    EnvironmentVariable::EnvironmentVariable() {
        settings = new QSettings();

        /** ComboBox para selecionar o backend multimídia para o QMediaPlayer */
        auto backend = new QCineComboBox::ComboBox();
        backend->addItems(audiobackend);
        backend->setCurrentText(settings->value("QT_MEDIA_BACKEND", "auto").toString());
        connect(backend, &QCineComboBox::ComboBox::enterBox, this, &EnvironmentVariable::enterBox);
        connect(backend, &QComboBox::currentTextChanged, this,
                &QCineEnvironmentVariable::EnvironmentVariable::changeBackEnd);

        /** Layout associado ao widget para inserir no QScroolArea */
        auto wscrool = new QWidget();
        auto vboxlayout = new QGridLayout(wscrool);
        vboxlayout->addWidget(new QLabel("QMEDIAPLAYER"), 0, 0, 1, 2);

        /** Preenchendo o layout */
        int i{1}, j{0};
        for (const auto &lst : list) {

            auto ck = new QCheckBox(lst);
            if (settings->value(ck->text(), checkFalse).toInt() == checkTrue)
                ck->setChecked(true);

            connect(ck, &QCheckBox::stateChanged, this, [&, ck](int i){
                settings->setValue(ck->text(), i);
            });

            if (i == 1) {

#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
                vboxlayout->addItem(new QSpacerItem(spSize, 0), i, 0);
                vboxlayout->addWidget(ck, i, 1);
#endif

            } else {
                if (i == 3) {
                    vboxlayout->addWidget(new QLabel("OPENGL"), i, 0, 1, 2);
                    j++;
                } else if (i + j == 11) {
                    if (checkNvidiaGpu()) {
                        vboxlayout->addWidget(new QLabel("NVIDIA"), i + j, 0, 1, 2);
                        j++;
                    } else
                        break;
                }

                vboxlayout->addItem(new QSpacerItem(spSize, 0), i + j, 0);
                vboxlayout->addWidget(ck, i + j, 1);
            }
            i++;
        }

        /** QScrollArea para deixar o tamanho da janela de configuração menor */
        auto scrollArea = new QScrollArea();
        scrollArea->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
        scrollArea->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
        scrollArea->setWidget(wscrool);
        scrollArea->setMinimumWidth(wscrool->size().width() + ajustScroolWidth);
        scrollArea->setFixedHeight(defScroolHeight);

        /** Layout principal */
        auto envlayout = new QGridLayout();
        envlayout->setContentsMargins(QMargins());

#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
        envlayout->addWidget(new QLabel(tr("QMediaPlayer Backend") + ":"), 0, 0);
        envlayout->addWidget(backend, 0, 1);
#endif

        envlayout->addWidget(scrollArea, 1, 0, 1, 2);

        /** Grupo para as variáveis de ambiente */
        auto *envbox = new QGroupBox(tr("Variables"));
        auto *envvar = new QVBoxLayout(envbox);
        envvar->addLayout(envlayout);

        /** Aba de variáveis de ambiente */
        auto *enviromentBox = new QVBoxLayout(this);
        enviromentBox->addWidget(envbox);
        enviromentBox->addStretch(1);
    }

    /**
     * Checando variáveis de ambiente que devem ou não serem definidas.
     */
    void EnvironmentVariable::checkEnvironmentVariable() {
        auto s = QSettings();

#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
        QString str = s.value("QT_MEDIA_BACKEND", "auto").toString();
        
        if (str != "auto")
            qputenv("QT_MEDIA_BACKEND", str.toStdString());

        if (s.value("LIBVA_DRIVER_NAME=iHD").toInt() == checkTrue)
            qputenv("LIBVA_DRIVER_NAME", "iHD");
#endif

        if (s.value("GST_VAAPI_ALL_DRIVERS=1").toInt() == checkTrue)
            qputenv("GST_VAAPI_ALL_DRIVERS", "1");

        if (s.value("MESA_GLTHREAD=true").toInt() == checkTrue)
            qputenv("MESA_GLTHREAD", "true");

        if (s.value("__GL_THREADED_OPTIMIZATIONS=1").toInt() == checkTrue)
            qputenv("__GL_THREADED_OPTIMIZATIONS", "1");

        if (s.value("__GL_SHADER_DISK_CACHE=1").toInt() == checkTrue)
            qputenv("__GL_SHADER_DISK_CACHE", "1");

        if (s.value("__GL_SHADER_DISK_CACHE_SKIP_CLEANUP=1").toInt() == checkTrue)
            qputenv("__GL_SHADER_DISK_CACHE_SKIP_CLEANUP", "1");

        if (s.value("__GL_YIELD=USLEEP").toInt() == checkTrue)
            qputenv("__GL_YIELD", "USLEEP"); // pode aumentar o uso da CPU

        if (s.value("__GL_SYNC_TO_VBLANK=0").toInt() == checkTrue)
            qputenv("__GL_SYNC_TO_VBLANK", "0"); // melhora o desempenho, mas pode resultar em tearing

        if (s.value("__GL_MaxFramesAllowed=1").toInt() == checkTrue)
            qputenv("__GL_MaxFramesAllowed","1"); // pode causar redução significativa na taxa de quadros da aplicação

        if (checkNvidiaGpu()) {
            if (s.value("__NV_PRIME_RENDER_OFFLOAD=1").toInt() == checkTrue)
                qputenv("__NV_PRIME_RENDER_OFFLOAD","1");

            if (s.value("__NV_PRIME_RENDER_OFFLOAD_PROVIDER=NVIDIA-G0").toInt() == checkTrue)
                qputenv("__NV_PRIME_RENDER_OFFLOAD_PROVIDER","NVIDIA-G0");

            if (s.value("__GLX_VENDOR_LIBRARY_NAME=nvidia").toInt() == checkTrue)
                qputenv("__GLX_VENDOR_LIBRARY_NAME","nvidia");

            if (s.value("EGL_NV_triple_buffer=1").toInt() == checkTrue)
                qputenv("EGL_NV_triple_buffer","1");
        }
    }

    /**
     * Função para selecionar o backend do QMediaPlayer para a variável de ambiente.
     * @param str - nome do backend.
     */
    void EnvironmentVariable::changeBackEnd(const QString &str) {
        settings->setValue("QT_MEDIA_BACKEND", str);
    }

    /**
     * Checkar se o Linux tem suporte e o driver Nvidia pra poder ativar as variáveis de ambiente.
     */
    bool EnvironmentVariable::checkNvidiaGpu() {
        QFile file("/proc/driver/nvidia/version");
        if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();
            return content.contains("NVRM", Qt::CaseInsensitive);
        }
        return false;
    }

} // QCineEnvironmentVariable