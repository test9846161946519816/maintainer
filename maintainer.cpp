#include "maintainer.h"
#include "ui_maintainer.h"

#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QSettings>

Maintainer::Maintainer(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Maintainer)
{
    ui->setupUi(this);
    setup();
}

Maintainer::~Maintainer()
{
    delete ui;
}

// do various setup tasks
void Maintainer::setup()
{
    version = getVersion();
    codename = getCodename();
    description = getDescription();
    QFont f( "Noto Sans", 16, QFont::Bold);
    ui->labelTitle->setFont(f);
    ui->labelTitle->setText(description + " " + codename);
    this->setWindowTitle(tr("Maintainer"));


/*
    // We want to sync the widths of every button in tab_3
    // Otherwise the alignment between the 2 groupboxes is non existent and it makes dr460nf1r3 and I sad
    int width = 0;
    auto buttons = this->ui->scrollArea->findChildren<QToolButton*>();
    for (auto element : qAsConst(buttons)) {
        // Let QT calculate the correct width for us.
        int b_width = element->sizeHint().width();
        if (b_width > width)
            width = b_width;
    }

    for (auto button : qAsConst(buttons)) {
        // Now that we know the size, we can force it.
        button->setMinimumWidth(width);
        // We need to force the maximum height here, otherwise weird things happen if you resize the window.
        // This would not be necessary if we used "fixed" size qtoolbuttons, but in that case the qtoolbuttons would be a different height sometimes
        button->setMaximumHeight(button->sizeHint().height());
    }

    //this->adjustSize();
*/
}

// Util function for getting bash command output and error code
Result Maintainer::runCmd(QString cmd, bool include_stderr)
{
    QProcess proc(this);
    if (include_stderr)
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start("/bin/bash", QStringList() << "-c" << cmd);
    // Wait forever
    proc.waitForFinished(-1);
    Result result = { proc.exitCode(), proc.readAll().trimmed() };
    return result;
}

QString Maintainer::getVersion()
{
    QString cmd = QString("lsb_release -r | cut -f2");
    return runCmd(cmd).output;
}

QString Maintainer::getCodename()
{
    QString cmd = QString("lsb_release -c | cut -f2");
    return runCmd(cmd).output;
}

QString Maintainer::getDescription()
{
    QString cmd = QString("lsb_release -d | cut -f2");
    return runCmd(cmd).output;
}

void Maintainer::errorMessage(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(nullptr, tr("Error"), tr("Unable to install."), QMessageBox::ok);
}

bool Maintainer::checkAndInstall(QString package)
{
    auto output = runCmd("pacman -Qq " + package, false);

    if (output.output == package || output.output == package + "-git")
        return true;
    
    if (QFile::exists("/usr/bin/pamac-installer")) {
        this->hide();
        runCmd("pamac-installer " + package);
    }
    else {
        this->hide();
        runCmd("alacritty --command pkexec pacman -S " + package);
    }

    output = runCmd("pacman -Qq " + package,  false);
    if (output.output == package)
        return true;
    else {
        errorMessage();
        this->show();
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////

void Maintainer::on_buttonDevice_clicked()
{
    if (!checkAndInstall("hardinfo"))
        return;
    this->hide();
    system("hardinfo");
    this->show();
}

void Maintainer::on_buttonPartition_clicked()
{
    if (!checkAndInstall("gparted"))
        return;
    this->hide();
    system("gparted");
    this->show();
}

void Maintainer::on_buttonNetwork_clicked()
{
    if (!checkAndInstall("bmon"))
        return;
    this->hide();
    system("bmon");
    this->show();
}

void Maintainer::on_buttonMonitor_clicked()
{
    if (!checkAndInstall("xfce4-taskmanager"))
        return;
    this->hide();
    system("xfce4-taskmanager");
    this->show();
}

void Maintainer::on_buttonMaintanance_clicked()
{
    
}

void Maintainer::on_buttonLog_clicked()
{
    
}

void Maintainer::on_buttonCleaner_clicked()
{
    if (!checkAndInstall("sweeper"))
        return;
    this->hide();
    system("sweeper");
    this->show();
}

void Maintainer::on_buttonAddRemove_clicked()
{
    if (!checkAndInstall("bauh"))
        return;
    this->hide();
    system("bauh");
    this->show();
}

void Maintainer::on_buttonBackup_clicked()
{
    if (!checkAndInstall("timeshift"))
        return;
    this->hide();
    system("timeshift");
    this->show();
}

void Maintainer::on_buttonAbout_clicked()
{
    
}

