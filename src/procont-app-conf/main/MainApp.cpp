#include <QApplication>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if( translator.load( ":/procont-app-conf_ru_RU.qm" ) )
        a.installTranslator( &translator );
    MainWindow w;
    w.show();

    return a.exec();
}
