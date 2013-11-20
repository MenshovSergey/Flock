#include <geometry/point_3d.h>
#include <scene3d/scene3d.h>
#include <scene/scene.h>
#include <world/world.h>
#include <objects/dynamic_object.h>
#include <objects/static_object.h>
#include <objects/visual_object.h>
#include <management/manager.h>
#include <behavior/behavior.h>

#include <qmath.h>     // подключаем математическую библиотеку
#include <vector>

using namespace std;

const static float pi=3.141593, k=pi/180; // глобальная переменная

const static double grad2rad = pi/180.;
const static float inf = -1000000.0;
double posic = 7;
double rtri = 0;

void gravity_xyz(vector<object::object_mod*> const & objects, map<object::object_mod*, object::controls*>& controls)
{
    size_t size = objects.size();
    int x_lim = 1;
    int y_lim = 1;
    int z_lim = 1;
    for (size_t i = 0; i < size; ++i)
    {
        if (controls.find(objects[i]) != controls.end())
        {
            state temp = objects[i]->get_state();
            double r = ((x_lim - temp.coord.x) * (x_lim - temp.coord.x) + (y_lim - temp.coord.y) * (y_lim - temp.coord.y) + (z_lim - temp.coord.z) * (z_lim - temp.coord.z));
            double f = 5 / r;
            point_3d new_force(f * (x_lim - temp.coord.x) / sqrt(r), f * (y_lim - temp.coord.y) / sqrt(r), f * (z_lim - temp.coord.z) / sqrt(r));
            (*controls.find(objects[i])).second->set_force(new_force);
        }
    }
}

scene::scene main_scene;
world::world universe(main_scene);
behavior::behavior_old gravity(&gravity_xyz);

object::manager * gravity_man = new object::manager(0);
object::dynamic_object * temp = new object::dynamic_object(1);
object::visual_object * vis = new object::visual_object;

point_3d p(0,0,0);

point_3d rotate(point_3d a,double angle)
{
    point_3d b(0,0,0);
    b.z = a.z;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) +a.y * cos(angle);
     return b;
}

std::vector<point_3d> objects;// конструктор класса scene_3d
scene_3d::scene_3d(QWidget* parent/*= 0*/) 
    : QGLWidget(parent) 
    , course_(0)
    , pitch_(0)
    , range_(10)
{    
   xRot = 0; 
   yRot = 0; 
   zRot = 0; 
   zTra = 0; 
   nSca = 1; 
   startTimer(40);
   // передает дальше указатель на объект parent
} 

/*virtual*/ void scene_3d::initializeGL() // инициализация
{
  glLoadIdentity();
    main_scene.init(*this);
    point_3d t_coord(0,0,0);
    point_3d t_speed(0,0,0);
    point_3d t_force(0,0,0);
    temp->init(t_coord, t_speed, t_force, 0.5, 0.1, 1, 1);
    temp->revisualise(vis);

    t_coord.x = 30;
    t_coord.y = 30;
    t_coord.z = 10;
    object::static_object * st = new object::static_object(257);
    st->init(t_coord, 1);

    vis->change_vis(true);

    gravity_man->init(gravity_xyz);
    gravity_man->reg(temp);
    gravity_man->reg(st);

    main_scene.add(vis);
    universe.add(gravity_man);
    universe.add(temp);
    universe.add(st);
 
}


/*virtual*/void scene_3d::resizeGL(int nWidth, int nHeight) // окно виджета
{ 

   glViewport(0, 0, nWidth, nHeight);
        double ratio = static_cast<double>(nWidth) / nHeight;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-14*ratio, 14*ratio, -14, 14, -14.0, 1000.0);
        glFrustum(-14*ratio, 14*ratio, -14, 14, 3.0, 1000.0);
    /*glMatrixMode(GL_PROJECTION); 
   glLoadIdentity();          
 
   // отношение высоты окна виджета к его ширине
   GLfloat ratio=(GLfloat)nWidth/(GLfloat)nHeight;
   glOrtho(-2*ratio, 2*ratio, -10, 10, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   // мировое окно
   if (nWidth>=nHeight)
      // параметры видимости ортогональной проекции
      glOrtho(-100.0/ratio, 100.0/ratio, -100.0, 100.0, -1.0, 1); 
   else
      glOrtho(-100.0, 100.0, -100.0*ratio, 100.0*ratio, -1.0, 1);      
   // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
   
   // параметры видимости перспективной проекции
   // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
   // плоскости отсечения (левая, правая, верхняя, нижняя, ближняя, дальняя)
  
   // поле просмотра*/
   //glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

/*virtual*/ void scene_3d::paintGL() // рисование
{
    double x,y,z;
    
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);        

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    

    glEnable(GL_COLOR_MATERIAL);


        //glScalef(nSca, nSca, nSca);        // масштабирование
        //glTranslatef(0.0f, zTra, 0.0f);    // трансляция     

    gluLookAt(range_*sin(course_ * grad2rad)*cos(pitch_*grad2rad),range_*cos(course_ * grad2rad)*cos(pitch_*grad2rad),range_*sin(pitch_*grad2rad),
                0,0,0,
                0,0,1);

/*        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X         
        glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
        glRotatef(zRot, 0.0f, 0.0f, 1.0f);        */
        
        //rtri += 10;        
        //glRotatef(-rtri,2.0,-3.0,1.0);
        
        //glColor4f(1.0, 0.0, 1,1);     
        
        
    for (int i = 0; i < objects.size(); i++)
    {
        x = objects[i].x - 1;
        y = objects[i].y - 1;
        z = objects[i].z;            
        glBegin(GL_TRIANGLES);
            glVertex3f(x,y,z);
            glVertex3f(x + 1, y + 1,z);
            glVertex3f(x + 1,y - 1,z);
        glEnd();
            
    }
        

    light();    

    // draw cube
/*    glPushMatrix();
    rtri += 10;        
    glRotatef(-rtri,2.0,-3.0,1.0);
    drawQuads();
    glPopMatrix();*/
    //drawLines();
    
    //swapBuffers();     

    objects.resize(0);    
}  

void scene_3d::light()
{
    glEnable(GL_LIGHTING);

    /*GLfloat light1_diffuse[] = {1, 1, 1};
    GLfloat light1_position[] = {0.0, 0.0, 0.0, 1.0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0008);)*/

    GLfloat light2_diffuse[] = {1, 1, 1};
    GLfloat light2_position[] = {(-posic - 1), -posic-1, (-posic - 1), 1};
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0008);

    GLfloat light3_diffuse[] = {1, 1, 1};
    GLfloat light3_position[] = {posic + 1, posic+1, posic + 1, 1.0};
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0008);

}

/*virtual*/void scene_3d::mouseMoveEvent(QMouseEvent* pe) 
{   
   // вычисление углов поворота
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height(); 
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width(); 
   
   ptrMousePosition = pe->pos();
   
   //updateGL(); // обновление изображения
}

/*virtual*/void scene_3d::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   // при нажатии пользователем кнопки мыши переменной ptrMousePosition 
   // будет присвоена координата указателя мыши 
   ptrMousePosition = pe->pos();  

   // ptrMousePosition = (*pe).pos(); // можно и так написать                          
} 

/*virtual*/void scene_3d::keyPressEvent(QKeyEvent* pe) 
{  
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
   }
   
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
   pitch_ += 1.0;
}

void scene_3d::rotate_down() // повернуть сцену вниз
{
   pitch_ -= 1.0;
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
    vector<point_3d>::iterator del = objects.begin() + number;
    objects.erase(del);
}

void scene_3d::timerEvent(QTimerEvent * event)
{
    //angle += 1;
    universe.update();
    main_scene.update();
    main_scene.render();
    updateGL();
}

void scene_3d::drawFish(look fish_look)
{
    objects.push_back(fish_look.coord);
 
    //updateGL();
}

void scene_3d::drawLines()
{ 
    
    glColor4f(1, 1, 0,0.3);
    glBegin(GL_LINES);//     

      glVertex3f(-posic,-posic,-posic);
      glVertex3f(posic,-posic,-posic);

    glEnd();

    glBegin(GL_LINES);//     

      glVertex3f(-posic,-posic,-posic);
      glVertex3f(-posic, posic, -posic);

    glEnd();

    glBegin(GL_LINES);//     

      glVertex3f(posic, posic,-posic);
      glVertex3f(posic,-posic,-posic);

    glEnd();

    glBegin(GL_LINES);    // 

      glVertex3f(posic,posic,-posic);
      glVertex3f(-posic, posic,-posic);

    glEnd();

    glBegin(GL_LINES);//     

      glVertex3f(-posic,-posic,-posic);
      glVertex3f(posic,-posic,-posic);

    glEnd();
    

    glBegin(GL_LINES);//     

      glVertex3f(posic, posic,posic);
      glVertex3f(posic,-posic,posic);

    glEnd();

    glBegin(GL_LINES);    // 

      glVertex3f(posic, posic, posic);
      glVertex3f(-posic, posic,posic);

    glEnd();
      
    glBegin(GL_LINES);
      
      glVertex3f(-posic,posic,posic);
      glVertex3f(-posic,-posic,posic);

    glEnd();

    glBegin(GL_LINES);
      glVertex3f(posic, -posic, posic);
      glVertex3f(-posic,-posic,posic);
    glEnd();



    glBegin(GL_LINES);
      
       glVertex3f(-posic,-posic,-posic);
       glVertex3f(-posic,-posic, posic);

    glEnd();

    glBegin(GL_LINES);
      
       glVertex3f(posic, posic,-posic);
       glVertex3f(posic, posic, posic);

    glEnd();

    glBegin(GL_LINES);
      
       glVertex3f(-posic, posic,-posic);
       glVertex3f(-posic, posic, posic);

    glEnd();

    glBegin(GL_LINES);
      
       glVertex3f(posic, -posic,-posic);
       glVertex3f(posic, -posic, posic);

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


///////////////////////////////////////////////////////////////////////////

