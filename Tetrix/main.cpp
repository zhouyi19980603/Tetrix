#include "myview.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    MyView view;
    view.show();

    //first commit
    //second commit
    return a.exec();
}
