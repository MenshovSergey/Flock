﻿#include <geometry/point_3d.h>
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

#include <qmath.h>     // подключаем математическую библиотеку
#include <vector>

using namespace std;

const static float pi=3.141593, k=pi/180; // глобальная переменная

const static double grad2rad = pi/180.;
const static float inf = -1000000.0;
double posic = 200;
double rtri = 0;

void gravity_xyz(vector<boost::shared_ptr<object::object_mod>> const & objects, map<boost::shared_ptr<object::object_mod>, 
	boost::shared_ptr<object::controls>>& controls)
{
    size_t size = objects.size();
    int x_lim = 0;
    int y_lim = 0;
    int z_lim = 0;
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

vector<boost::shared_ptr<object::dynamic_object> > temps;
vector<boost::shared_ptr<object::visual_object> > viss;
//vector<boost::shared_ptr<object::dynamic_object> > temps2;
//vector<boost::shared_ptr<object::visual_object>> viss2;
boost::shared_ptr<object::dynamic_object> target;
//object::flock * main_flock = new object::flock(2);
//object::flock * second_flock = new object::flock(3);
boost::shared_ptr<object::flock> main_flock = boost::make_shared<object::flock>(2);
//boost::shared_ptr<object::flock> second_flock = boost::make_shared<object::flock>(3);
point_3d p(0,0,0);

point_3d rotate(point_3d a,double angle)
{
    point_3d b(0,0,0);
    b.z = a.z;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) +a.y * cos(angle);
     return b;
}

//std::vector<look> objects;// конструктор класса scene_3d

scene_3d::scene_3d(QWidget* parent/*= 0*/)
    : QGLWidget(parent)
    , course_(0)
    , pitch_(0)
    , range_(40)
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
    main_scene.init(*this); //DONEEEEEEEEEEEEEEEEEEEE
    point_3d t_speed(0,0,0);
    point_3d t_force(0,0,0);
	temps.resize(100);
	viss.resize(100);
	//temps2.resize(100);
	//viss2.resize(100);
	boost::shared_ptr<behavior::behavior_cohere>  flocker = boost::make_shared< behavior::behavior_cohere>(15., 1);
	//boost::shared_ptr<behavior::behavior_cohere> flocker2 = boost::make_shared< behavior::behavior_cohere>(10., 0.01);

	universe.add(main_flock);
	//universe.add(second_flock);

    look model_vis;
    model_vis.v1.y = -0.5;
    model_vis.v2.y = 0.5;
    model_vis.v3.x = 3.;
    model_vis.v4.z = 0.5;

    
    model_vis.color.x = 0.9;
    model_vis.color.y = 0.3;
    model_vis.color.z = 0.6;
    
    /*look model_vis2 = model_vis;
	model_vis2.color.x = 0;
    model_vis2.color.y = .5;
    model_vis2.color.z = .5;*/

	look model_vis_target;
	model_vis_target.v1.y = -2;
	model_vis_target.v1.x = -2;
	model_vis_target.v1.z = -1;

    model_vis_target.v2.y = 2;
	model_vis_target.v2.x = -2;
	model_vis_target.v2.z = -1;

    model_vis_target.v3.x = 2;
	model_vis_target.v3.y = 0;
	model_vis_target.v3.z = -1;

    model_vis_target.v4.z = 3;
    model_vis_target.v4.x = 0.5;
	
    model_vis_target.color.x = 1;
    model_vis_target.color.y = 0;
    model_vis_target.color.z = 0;


    boost::shared_ptr<object::visual_object>  target_vis;
	
	target = boost::make_shared<object::dynamic_object>(19);
    target_vis = boost::make_shared< object::visual_object>(model_vis_target);
	boost::shared_ptr<behavior::behavior_pursuit>  seeker = boost::make_shared <behavior::behavior_pursuit>(target);


	point_3d target_pos(0, 0, 0);

	target->init(target_pos, target_pos,target_pos, 4, 1, 1, 1);
	target->revisualise(target_vis);
	target_vis->change_vis(true);
	main_scene.add(target_vis);
	universe.add(target);

	main_flock->add_b(flocker);
	main_flock->add_b(seeker);
	//second_flock->add_b(flocker2);
	for (int i = 0; i < temps.size(); ++i)
	{
		temps[i] = boost::make_shared< object::dynamic_object>(0);
		viss[i] = boost::make_shared< object::visual_object>(model_vis);

		//temps2[i] = boost::make_shared< object::dynamic_object>(0);
		//viss2[i] = boost::make_shared< object::visual_object>(model_vis2);

		point_3d t_coord(i,sin(static_cast<double>(i)),cos(static_cast<double>(i)));
        temps[i]->init(t_coord, t_speed, t_force, 1, 0.3, 1, 1);
        temps[i]->revisualise(viss[i]);
		viss[i]->change_vis(true);
		main_flock->reg(temps[i]);
		main_scene.add(viss[i]);
        universe.add(temps[i]);

	    /*point_3d t_coord2(-i * 10.,sin(static_cast<double>(i)),cos(static_cast<double>(i)));
        temps2[i]->init(t_coord2, t_speed, t_force, 0.5, 0.1, 1, 1);
        temps2[i]->revisualise(viss2[i]);
		viss2[i]->change_vis(true);
		second_flock->reg(temps2[i]);
		main_scene.add(viss2[i]);
        universe.add(temps2[i]);*/
	}
    flocker->init(main_flock->get_members());
    //flocker2->init(second_flock->get_members());
    
	/*
    gravity_man->init(gravity_xyz);
    gravity_man->reg(temp);
    gravity_man->reg(st);
	*/

}


/*virtual*/void scene_3d::resizeGL(int nWidth, int nHeight) // окно виджета
{

      glViewport(0, 0, nWidth, nHeight);
        double ratio = static_cast<double>(nWidth) / nHeight;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-14*ratio, 14*ratio, -14, 14, -14.0, 1000.0);

        glFrustum(-10*ratio, 10*ratio, -10, 10, 20.0, 1000.0);
   
}

/*virtual*/ void scene_3d::paintGL() // рисование
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
	state_vis center = target->get_state_vis();
    gluLookAt(range_*sin(course_ * grad2rad)*cos(pitch_*grad2rad) + center.coord.x,
		        range_*cos(course_ * grad2rad)*cos(pitch_*grad2rad) + center.coord.y,
				range_*sin(pitch_*grad2rad) + center.coord.z,
                center.coord.x, center.coord.y, center.coord.z,
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

    //swapBuffers();

    //objects.resize(0);
}

void scene_3d::light()
{
    glEnable(GL_LIGHTING);
	state light_pos = target->get_state();
    GLfloat light1_diffuse[] = {1, 1, 1};
    GLfloat light1_position[] = {light_pos.coord.x, light_pos.coord.y, light_pos.coord.z, 1.0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0005);

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

	state_vis temp = target->get_state_vis();
	double a = 5;
    point_3d temp_force(a * (cos(temp.coord.y) - 0.5 *temp.coord.x/posic), 0.9 * a * (cos(temp.coord.z) - 0.5 *temp.coord.y/posic), a * (cos(temp.coord.x) - 0.5 * temp.coord.z/posic)); 
	target->set_force(temp_force);
    universe.update();
    main_scene.update();
    main_scene.render();
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

///////////////////////////////////////////////////////////////////////////

