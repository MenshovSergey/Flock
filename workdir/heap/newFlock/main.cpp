#include "world.h"
#include <QApplication>
#include "MyWorld1.h"
#include "StaticObject.h"
#include "QLinearGradient"
#include "QRadialGradient"
#include "QPainter"
#include "cstdio"
#include "QFile"
#include "QTextStream"
#include "QtDebug"
#include "iostream"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    World w;
    Static_Object u ;
    u.add();
    //freopen("1.txt","w",stdout);
    //cout << u.x;
    w.show();

    return a.exec();
}
