#include <geometry/point_3d.h>
#include <scene3d/scene3d.h>
#include <scene/scene.h>
#include <world/world.h>
#include <objects/dynamic_object.h>
#include <objects/static_object.h>
#include <objects/visual_object.h>
#include <management/manager.h>
#include <behavior/behavior.h>
#include <behavior/behavior_cohere.h>
#include <behavior/behavior_pursuit.h>

#include <qmath.h>
#include <vector>

using namespace std;

const static float pi=3.141593, k=pi/180;

const static double grad2rad = pi/180.;
const static float inf = -1000000.0;
double posic = 200;
double rtri = 0;

point_3d rotate(point_3d a,double angle)
{
    point_3d b(0,0,0);
    b.z = a.z;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) +a.y * cos(angle);
     return b;
}

scene_3d::scene_3d(QWidget* parent/*= 0*/)
    : QGLWidget(parent)
    , course_(0)
    , pitch_(0)
    , range_(40)
    , center(0, 0, 0)
{
   xRot = 0;
   yRot = 0;
   zRot = 0;
   zTra = 0;
   nSca = 1;
   startTimer(40);
}

void scene_3d::initializeGL() 
{
  glLoadIdentity();

}

void scene_3d::resizeGL(int nWidth, int nHeight) // окно виджета
{

      glViewport(0, 0, nWidth, nHeight);
        double ratio = static_cast<double>(nWidth) / nHeight;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-14*ratio, 14*ratio, -14, 14, -14.0, 1000.0);

        glFrustum(-10*ratio, 10*ratio, -10, 10, 20.0, 1000.0);
      TwWindowSize(nWidth, nHeight);
}

void scene_3d::paintGL()
{
    //double x,y,z;

    //glEnable(GL_ALPHA_TEST);
    
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_COLOR_MATERIAL);


        //glScalef(nSca, nSca, nSca);        // масштабирование
        //glTranslatef(0.0f, zTra, 0.0f);    // трансляция
	//state_vis center = target->get_state_vis();
    gluLookAt(range_*sin(course_ * grad2rad)*cos(pitch_*grad2rad) + center.x,
		        range_*cos(course_ * grad2rad)*cos(pitch_*grad2rad) + center.y,
				range_*sin(pitch_*grad2rad) + center.z,
                center.x, center.y, center.z,
                0,0,1);

/*        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
        glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
        glRotatef(zRot, 0.0f, 0.0f, 1.0f);        */

        //rtri += 10;
        //glRotatef(-rtri,2.0,-3.0,1.0);

        //glColor4f(1.0, 0.0, 1,1);

    point_3d vertex1, vertex2, vertex3, vertex4;
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->is_visible)
        {
            vertex1 = objects[i]->coord + objects[i]->v1;
            vertex2 = objects[i]->coord + objects[i]->v2;
            vertex3 = objects[i]->coord + objects[i]->v3;
            vertex4 = objects[i]->coord + objects[i]->v4;

            glColor4f(objects[i]->color.x, objects[i]->color.y, objects[i]->color.z,1);
            glBegin(GL_TRIANGLES);
                glVertex3f(vertex1.x,vertex1.y,vertex1.z);
                glVertex3f(vertex2.x,vertex2.y,vertex2.z);
                glVertex3f(vertex3.x,vertex3.y,vertex3.z);
            glEnd();

            glColor4f(objects[i]->color.x * 0.9, objects[i]->color.y * 0.8, objects[i]->color.z * 0.8,1);
            glBegin(GL_TRIANGLES);
                glVertex3f(vertex1.x,vertex1.y,vertex1.z);
                glVertex3f(vertex2.x,vertex2.y,vertex2.z);
                glVertex3f(vertex4.x,vertex4.y,vertex4.z);
            glEnd();
            
            glColor4f(objects[i]->color.x * 0.6, objects[i]->color.y * 0.7, objects[i]->color.z * 0.6,1);
            glBegin(GL_TRIANGLES);
                glVertex3f(vertex1.x,vertex1.y,vertex1.z);
                glVertex3f(vertex3.x,vertex3.y,vertex3.z);
                glVertex3f(vertex4.x,vertex4.y,vertex4.z);
            glEnd();
            glColor4f(objects[i]->color.x * 0.4, objects[i]->color.y * 0.4, objects[i]->color.z * 0.5,1);
            glBegin(GL_TRIANGLES);
                glVertex3f(vertex2.x,vertex2.y,vertex2.z);
                glVertex3f(vertex3.x,vertex3.y,vertex3.z);
                glVertex3f(vertex4.x,vertex4.y,vertex4.z);
            glEnd();
        }

    }


    light();

    // draw cube
   glPushMatrix();
    //rtri += 10;
    //glRotatef(-rtri,2.0,-3.0,1.0);
    drawQuads();
    glPopMatrix();
    drawLines();

    TwDraw();

    //swapBuffers();

    //objects.resize(0);
}

void scene_3d::light()
{
    glEnable(GL_LIGHTING);
	/*state light_pos = target->get_state();
    GLfloat light1_diffuse[] = {1, 1, 1};
    GLfloat light1_position[] = {light_pos.coord.x, light_pos.coord.y, light_pos.coord.z, 1.0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0005);*/

    GLfloat light2_diffuse[] = {1, 1, 1};
    GLfloat light2_position[] = {(-posic - 1), -posic-1, (-posic - 1), 1};
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0008);

    GLfloat light3_diffuse[] = {1, 1, 1};
    GLfloat light3_position[] = {posic + 1, posic+1, posic + 1, 1.0};
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0008);

}

void scene_3d::mouseMoveEvent(QMouseEvent* pe)
{
   // вычисление углов поворота
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();
   TwMouseMotion(pe->x(), pe->y());
   //updateGL(); // обновление изображения
}

void scene_3d::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   // при нажатии пользователем кнопки мыши переменной ptrMousePosition
   // будет присвоена координата указателя мыши
   ptrMousePosition = pe->pos();
   TwMouseMotion(pe->x(), pe->y());
   TwMouseAction act;
   act = TW_MOUSE_PRESSED;
   TwMouseButtonID id;
   if (pe->button() == Qt::LeftButton)
   {
       id = TW_MOUSE_LEFT;
   }
   if (pe->button() == Qt::RightButton)
   {
       id = TW_MOUSE_RIGHT;
   }
   if (pe->button() == Qt::MiddleButton)
   {
       id = TW_MOUSE_MIDDLE;
   }
   rtri = pe->buttons();
   TwMouseButton(act,id);
   // ptrMousePosition = (*pe).pos(); // можно и так написать
}

void scene_3d::mouseReleaseEvent(QMouseEvent* pe) 
{
   ptrMousePosition = pe->pos();
   TwMouseMotion(pe->x(), pe->y());
   TwMouseAction act;
   act = TW_MOUSE_RELEASED;
   TwMouseButtonID id;
   if (pe->button() == Qt::LeftButton)
   {
       id = TW_MOUSE_LEFT;
   }
   if (pe->button() == Qt::RightButton)
   {
       id = TW_MOUSE_RIGHT;
   }
   if (pe->button() == Qt::MiddleButton)
   {
       id = TW_MOUSE_MIDDLE;
   }
   rtri = pe->buttons();
   TwMouseButton(act,id);
   // ptrMousePosition = (*pe).pos(); // можно и так написать
}

void scene_3d::keyPressEvent(QKeyEvent* pe)
{
    Qt::KeyboardModifiers mod_inc = pe->modifiers();
    int mod_out = TW_KMOD_NONE;

    if ((mod_inc & Qt::ShiftModifier) == Qt::ShiftModifier)
    {
        mod_out = mod_out | TW_KMOD_SHIFT;
    }
    if ((mod_inc & Qt::ControlModifier) == Qt::ControlModifier)
    {
        mod_out = mod_out | TW_KMOD_CTRL;
    }
    if ((mod_inc & Qt::AltModifier) == Qt::AltModifier)
    {
        mod_out = mod_out | TW_KMOD_ALT;
    }

    int t_key = pe->key();
    

    switch (pe->key())
    {
        case Qt::Key_Plus:
            scale_plus();     // приблизить сцену
        break;

        case Qt::Key_Equal:
            scale_plus();     // приблизить сцену
        break;

        case Qt::Key_Minus:
            scale_minus();    // удалиться от сцены
        break;

        case Qt::Key_Up:
            rotate_up();      // повернуть сцену вверх
        break;

        case Qt::Key_Down:
            rotate_down();    // повернуть сцену вниз
        break;

        case Qt::Key_Left:
        rotate_left();     // повернуть сцену влево
        break;

        case Qt::Key_Right:
            rotate_right();   // повернуть сцену вправо
        break;

        case Qt::Key_PageDown:
            translate_down(); // транслировать сцену вниз
        break;

        case Qt::Key_PageUp:
            translate_up();   // транслировать сцену вверх
        break;

        case Qt::Key_Space:  // клавиша пробела
            defaultScene();   // возвращение значений по умолчанию
        break;

        case Qt::Key_Escape: // клавиша "эскейп"
            this->close();    // завершает приложение
        break;
        case Qt::Key_Enter:
            t_key = TW_KEY_RETURN;
        break;
        case Qt::Key_Backspace:
            t_key = TW_KEY_BACKSPACE;
        break;
        case Qt::Key_Delete:
            t_key = TW_KEY_DELETE;
        break;
    }

    TwKeyPressed(t_key, mod_out);
   //updateGL(); // обновление изображения
}

void scene_3d::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void scene_3d::scale_minus() // удалиться от сцены
{
   nSca = nSca/1.1;
}

void scene_3d::rotate_up() // повернуть сцену вверх
{
   if (pitch_ < 89.)
   {
       pitch_ += 1.0;
   }
}

void scene_3d::rotate_down() // повернуть сцену вниз
{
   if (pitch_ > -89.)
   {
       pitch_ -= 1.0;
   }
}

void scene_3d::rotate_left() // повернуть сцену влево
{
   course_ -= 1.0;
}

void scene_3d::rotate_right() // повернуть сцену вправо
{
   course_ += 1.0;
}

void scene_3d::translate_down() // транслировать сцену вниз
{
   range_ -= 0.5;
}

void scene_3d::translate_up() // транслировать сцену вверх
{
   range_ += 0.5;
}

void scene_3d::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=0; yRot=0; zRot=0; zTra=0; nSca=1;
}

void scene_3d::deleteFish(int number)
{
	//vector<myPtr<look>::my_ptr >::iterator del = boost::make_shared<objects.begin() + number;
    //objects.erase(del);
}

void scene_3d::timerEvent(QTimerEvent * event)
{
    //angle += 1;

    updateGL();
}


void scene_3d::drawLines()
{

    glColor4f(1, 1, 0,0.3);
	glLineWidth(10);
	double l_posic = posic - 1;
    glBegin(GL_LINES);//

      glVertex3f(-l_posic,-l_posic,-l_posic);
      glVertex3f(l_posic,-l_posic,-l_posic);

    glEnd();

    glBegin(GL_LINES);//

      glVertex3f(-l_posic,-l_posic,-l_posic);
      glVertex3f(-l_posic, l_posic, -l_posic);

    glEnd();

    glBegin(GL_LINES);//

      glVertex3f(l_posic, l_posic,-l_posic);
      glVertex3f(l_posic,-l_posic,-l_posic);

    glEnd();

    glBegin(GL_LINES);    //

      glVertex3f(l_posic,l_posic,-l_posic);
      glVertex3f(-l_posic, l_posic,-l_posic);

    glEnd();

    glBegin(GL_LINES);//

      glVertex3f(-l_posic,-l_posic,-l_posic);
      glVertex3f(l_posic,-l_posic,-l_posic);

    glEnd();


    glBegin(GL_LINES);//

      glVertex3f(l_posic, l_posic,l_posic);
      glVertex3f(l_posic,-l_posic,l_posic);

    glEnd();

    glBegin(GL_LINES);    //

      glVertex3f(l_posic, l_posic, l_posic);
      glVertex3f(-l_posic, l_posic,l_posic);

    glEnd();

    glBegin(GL_LINES);

      glVertex3f(-l_posic,l_posic,l_posic);
      glVertex3f(-l_posic,-l_posic,l_posic);

    glEnd();

    glBegin(GL_LINES);
      glVertex3f(l_posic, -l_posic, l_posic);
      glVertex3f(-l_posic,-l_posic,l_posic);
    glEnd();



    glBegin(GL_LINES);

       glVertex3f(-l_posic,-l_posic,-l_posic);
       glVertex3f(-l_posic,-l_posic, l_posic);

    glEnd();

    glBegin(GL_LINES);

       glVertex3f(l_posic, l_posic,-l_posic);
       glVertex3f(l_posic, l_posic, l_posic);

    glEnd();

    glBegin(GL_LINES);

       glVertex3f(-l_posic, l_posic,-l_posic);
       glVertex3f(-l_posic, l_posic, l_posic);

    glEnd();

    glBegin(GL_LINES);

       glVertex3f(l_posic, -l_posic,-l_posic);
       glVertex3f(l_posic, -l_posic, l_posic);

    glEnd();
}

void scene_3d::drawQuads()
{
    glColor4f(1.0,1.0,0,0.3);
    glBegin(GL_QUADS);
      glVertex3f(-posic, -posic, -posic);
      glVertex3f(posic, -posic,  -posic);
      glVertex3f(posic, -posic,   posic);
      glVertex3f(-posic, -posic,  posic);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-posic, posic, -posic);
      glVertex3f(posic,  posic,  -posic);
      glVertex3f(posic,  posic,  posic);
      glVertex3f(-posic, posic,  posic);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-posic, -posic, -posic);
      glVertex3f(-posic, posic,  -posic);
      glVertex3f(posic, posic,   -posic);
      glVertex3f(posic, -posic,  -posic);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-posic, -posic, posic);
      glVertex3f(-posic, posic,  posic);
      glVertex3f(posic, posic,   posic);
      glVertex3f(posic, -posic,  posic);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-posic, -posic, -posic);
      glVertex3f(-posic, -posic,  posic);
      glVertex3f(-posic, posic,   posic);
      glVertex3f(-posic, posic,  -posic);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(posic, -posic, -posic);
      glVertex3f(posic, -posic,  posic);
      glVertex3f(posic, posic,   posic);
      glVertex3f(posic, posic,  -posic);
    glEnd();
}

void scene_3d::add_object(boost::shared_ptr<look>  new_object)
{
	objects.push_back(new_object);
}
void scene_3d::delete_object()
{

}

