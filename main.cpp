#include "maintainer.h"
#include <QApplication>
#include <QIcon>
#include <QLocale>
#include <QTranslator>
#include <unistd.h>

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("kayos");
    QCoreApplication::setApplicationName("kayos-Maintainer");
#if QT_VERSION >= 0x050600
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/usr/share/pixmaps/kayos.png"));

    QTranslator qtTran;
    qtTran.load(QString("qt_") + QLocale::system().name());
    a.installTranslator(&qtTran);


    if (getuid() != 0) {
        Maintainer w;
        w.show();
        return a.exec();
    } else {
        QApplication::beep();
        QMessageBox::critical(0, QString::null,
            QApplication::tr("You must run this program as normal user."));
        return 1;
    }
}
