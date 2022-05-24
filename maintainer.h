#ifndef Maintainer_H
#define Maintainer_H

#include <QMessageBox>

namespace Ui {
class Maintainer;
}

struct Result {
    int exitCode;
    QString output;
};

class Maintainer : public QDialog {
    Q_OBJECT

public:
    explicit Maintainer(QWidget* parent = 0);
    ~Maintainer();

    Result runCmd(QString cmd, bool include_stderr = true);
    QString getVersion();
    QString getCodename();
    QString getDescription();

    QString version,codename,description;
    QString output;

    void setup();

private slots:
    void on_buttonDevice_clicked();
    void on_buttonPartition_clicked();
    void on_buttonNetwork_clicked();
    void on_buttonMonitor_clicked();
    void on_buttonMaintanance_clicked();
    void on_buttonLog_clicked();
    void on_buttonCleaner_clicked();
    void on_buttonAddRemove_clicked();
    void on_buttonBackup_clicked();
    void on_buttonAbout_clicked();

private:
    Ui::Maintainer* ui;
    void errorMessage();
    bool checkAndInstall(QString packagename);
};

#endif
