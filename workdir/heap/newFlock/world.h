#pragma once
#include <QVector>
#include <QMainWindow>
#include "Object.h"
#include "StaticObject.h"

struct World : public QMainWindow
{

public:

    Q_OBJECT
    //void update();
    //void add_Object(Object&);
    void paintEvent(QPaintEvent *);
    //void erase(Object const&);
    Object* t;



};


