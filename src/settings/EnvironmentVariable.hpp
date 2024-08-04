#ifndef QCINE_ENVIRONMENTVARIABLE_HPP
#define QCINE_ENVIRONMENTVARIABLE_HPP

#include <QCheckBox>
#include <QFile>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QSettings>
#include <QSpacerItem>
#include <QWidget>

#include <ComboBox.hpp>

namespace QCineEnvironmentVariable {

    class EnvironmentVariable : public QWidget {
        Q_OBJECT

    public:
        explicit EnvironmentVariable();

        static void checkEnvironmentVariable();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void enterBox(bool b);

#pragma clang diagnostic pop

    private Q_SLOTS:
        void changeBackEnd(const QString &str);

    private:
        static bool checkNvidiaGpu();

        QScrollArea *scrollArea{};
        QGridLayout *envlayout{};
        QGroupBox *envbox{};
        QVBoxLayout *envvar{}, *enviromentBox{};

        QStringList audiobackend{"auto", "ffmpeg", "gstreamer"};
        QSettings *settings{};
        QStringList list = {
                "LIBVA_DRIVER_NAME=iHD",
                "GST_VAAPI_ALL_DRIVERS=1",
                "MESA_GLTHREAD=true",
                "__GL_THREADED_OPTIMIZATIONS=1",
                "__GL_SHADER_DISK_CACHE=1",
                "__GL_SHADER_DISK_CACHE_SKIP_CLEANUP=1",
                "__GL_YIELD=USLEEP",
                "__GL_SYNC_TO_VBLANK=0",
                "__GL_MaxFramesAllowed=1",
                "__NV_PRIME_RENDER_OFFLOAD=1",
                "__NV_PRIME_RENDER_OFFLOAD_PROVIDER=NVIDIA-G0",
                "__GLX_VENDOR_LIBRARY_NAME=nvidia",
                "EGL_NV_triple_buffer=1"
        };
    };

} // QCineEnvironmentVariable

#endif //QCINE_ENVIRONMENTVARIABLE_HPP
