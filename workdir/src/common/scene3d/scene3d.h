#pragma once
#include <geometry/point_3d.h>
#include <QtGui>  
#include "typedef/typedef.h"
#include <containers/look.h>
#include <QtOpenGL\qgl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <QGLWidget>
#include <qwidget.h>

using namespace std;
// подключаем класс QGLWidget

class scene_3d : public QGLWidget // класс scene_3d наследует встроенный класс QGLWidget
{
public:
    scene_3d(QWidget* parent = 0);

protected:
    // метод для проведения инициализаций, связанных с OpenGL
    /*virtual*/ void initializeGL();
    // метод вызывается при изменении размеров окна виджета
    /*virtual*/ void resizeGL(int nWidth, int nHeight);
    // метод, чтобы заново перерисовать содержимое виджета
    /*virtual*/ void paintGL();
    void mouseMoveEvent(QMouseEvent* pe);
    void mousePressEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void keyPressEvent(QKeyEvent* pe);

public:
    //void drawFish(look);
    void timerEvent(QTimerEvent * event);
    void deleteFish(int number);
    void scale_plus();     // приблизить сцену
    void scale_minus();    // удалиться от сцены
    void rotate_up();      // повернуть сцену вверх
    void rotate_down();    // повернуть сцену вниз
    void rotate_left();    // повернуть сцену влево
    void rotate_right();   // повернуть сцену вправо
    void translate_down(); // транслировать сцену вниз
    void translate_up();   // транслировать сцену вверх
    void defaultScene();   // наблюдение сцены по умолчанию
    void drawLines();
    void light();
    void drawQuads();
    void add_object(boost::shared_ptr<look>  new_object);
    void delete_object();

//private:
    double course_;
    double range_;
    double pitch_;
    point_3d center;
    std::vector<boost::shared_ptr<look>> objects;
    scene_3d(scene_3d const&){
	}

    GLfloat xRot; // переменная хранит угол поворота вокруг оси X
    GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
    GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
    GLfloat zTra; // переменная хранит величину трансляции оси Z
    GLfloat nSca; // переменная отвечает за масштабирование объекта

    QPoint ptrMousePosition; // координата указателя мыши

};