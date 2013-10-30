#include "world.h"
#include "Object.h"
#include "QPainter"
#include "QRadialGradient"
#include "iostream"
#include "my.h"
using namespace std;


void World::paintEvent(QPaintEvent*){
    QRadialGradient gradient(50, 50, 50, 30, 30);
    QPainter painter;
     painter.begin(this);
     gradient.setColorAt(0.2, Qt::white);
     gradient.setColorAt(0.8, Qt::green);
     gradient.setColorAt(1, Qt::black);
     painter.setBrush(gradient);
     cout << My::t.size();
     //if (t->objects.size() != 0)
     //painter.drawEllipse(t->objects[0]->getX(),t->objects[0]->getY(), 100, 100);
     painter.end();
     QWidget::update();
}


