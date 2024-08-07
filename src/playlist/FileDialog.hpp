#ifndef QCINE_FILEDIALOG_HPP
#define QCINE_FILEDIALOG_HPP

#include <QFileDialog>
#include <QResizeEvent>
#include <QStandardPaths>

#include <SettingsManager.hpp>
#include <Style.hpp>

namespace QCineFileDialog {

    class FileDialog : public QFileDialog {
        Q_OBJECT

    public:
        explicit FileDialog();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    Q_SIGNALS:
        void dialogShow(bool b);

#pragma clang diagnostic pop

    protected:
        void showEvent(QShowEvent *event) override;

        void hideEvent(QHideEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

        void enterEvent(QEnterEvent *event) override;
    };

} // QCineFileDialog

#endif //QCINE_FILEDIALOG_HPP
