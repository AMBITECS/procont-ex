#include <QApplication>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if( translator.load( ":/procont-app-conf_ru_RU.qm" ) )
        a.installTranslator( &translator );

    auto config = QString();
    auto directory = QString();
    for(auto i=0;i<argc;i++)
    {
        if(QString(argv[i]) == "--config" || QString(argv[i]) == "-c")
            config = (++i <= argc) ? argv[i] : QString();
        if(QString(argv[i]) == "--directory" || QString(argv[i]) == "-d")
            directory = (++i <= argc) ? argv[i] : QString();
    }

    MainWindow::setDirectory(directory);
    MainWindow::setConfig(config);
    MainWindow::instance()->show();

    return a.exec();
}
