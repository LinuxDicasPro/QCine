/**
 * QCine - Reprodutor multimídia de caráter cinematográfico inspirado no Windows Media Player.
 *
 * Embora a inspiração, o projeto não tem a intenção de copiar a interface do Windows Media Player.
 *
 * Criado para ser altamente personalizável com aparência moderna e elegante.
 *
 * Licença: GNU General Public License Version 3 (GLPv3)
 *
 * Mantenedor: Mauricio Ferrari
 * E-Mail: m10ferrari1200@gmail.com
 * Telegram: @maurixnovatrento
 */

#include <SingleApplication>

#include <QLoggingCategory>
#include <QCommandLineParser>

#include <Debug.hpp>
#include <EnvironmentVariable.hpp>
#include <Fonts.hpp>
#include <MessageReceiver.hpp>
#include <QCine.hpp>
#include <SettingsManager.hpp>
#include <Style.hpp>
#include <Translator.hpp>
#include <Version.hpp>

int main(int argc, char *argv[]) {
    SingleApplication QCINE(argc, argv, true, SingleApplication::Mode::SecondaryNotification);
    QCineMessageReceiver::MessageReceiver msg;

    /** Definições do Programa */
    QApplication::setApplicationName("QCine");
    QApplication::setOrganizationName(QApplication::applicationName());
    QApplication::setApplicationDisplayName(QApplication::applicationName());
    QApplication::setApplicationVersion(VERSION);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"

    QLoggingCategory::setFilterRules("*.error=false\n*.warning=false\n*.critical=false\n*.info=false");
    if (!DEBUG)
        QLoggingCategory::setFilterRules("*=false");

#pragma clang diagnostic pop

    /** Debug inicial */
    auto *debug = new QCineDebug::Debug();
    debug->msg("Versão do programa", "Main", {QApplication::applicationVersion()});
    debug->msg("Pid do programa", "Main", {QString::number(QApplication::applicationPid())});

    QCineEnvironmentVariable::EnvironmentVariable::checkEnvironmentVariable();
    QApplication::setPalette(QCineStyle::Style::darkTheme());
    QApplication::setFont(QCineFonts::Fonts().getFont());

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings, true);

//    AA_CompressHighFrequencyEvents
//    AA_ForceRasterWidgets
//    AA_UseDesktopOpenGL
//    AA_UseOpenGLES
//    AA_UseSoftwareOpenGL
//    AA_ShareOpenGLContexts

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(QCINE);

    if (QCINE.isSecondary()) {
        debug->msg("Nova instância, passando os argumentos", "Main");
        QCINE.sendMessage(parser.positionalArguments().join('\n').toUtf8());
        return 0;
    }

    /** Interface gráfica */
    QCine::QCine QCine;
    if (!parser.positionalArguments().isEmpty()) {
        debug->msg("Passando os argumentos da primeira instância", "Main");
        QCine.addArgs(parser.positionalArguments());
    }

    QObject::connect(&QCINE, &SingleApplication::instanceStarted, [&QCine, &debug]() {
        debug->msg("Trazendo janela para o topo", "Main");

#if defined(Q_OS_WIN)
        QCine.activateWindow();
#elif defined(Q_OS_LINUX)
        auto eFlags = QCine.windowFlags();
        QCine.setWindowFlags(eFlags | Qt::WindowStaysOnTopHint);
        QCine.show();
        QCine.setWindowFlags(eFlags);
        QCine.show();
#endif

    });

    QObject::connect(&QCINE, &SingleApplication::receivedMessage, &msg,
                     &QCineMessageReceiver::MessageReceiver::receivedMessage);
    QObject::connect(&msg, &QCineMessageReceiver::MessageReceiver::args, &QCine,
                     &QCine::QCine::addArgs);

    QCineTranslator::Translator().translate();

    if (QCineSettingsManager::SettingsManager().windowMaximize())
        QCine.showMaximized();
    else
        QCine.show();

    return SingleApplication::exec();
}
