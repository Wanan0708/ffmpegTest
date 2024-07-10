#include "widget.h"

#include <QApplication>
#include <QFile>

#undef main
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qssFile(":/new/prefix1/style.qss");
    if (qssFile.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(qssFile.readAll());
    }
    qssFile.close();

    Widget w;
    w.show();
    return a.exec();
}
