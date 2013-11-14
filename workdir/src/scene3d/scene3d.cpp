#include <geometry/point_3d.h>
#include <scene3d/scene3d.h>
#include <scene/scene.h>
#include <world/world.h>
#include <objects/dynamic_object.h>
#include <objects/static_object.h>
#include <objects/visual_object.h>
#include <management/manager.h>
#include <behavior/behavior.h>


using namespace std;

const static float pi=3.141593f, k=pi/180; // ãëîáàëüíàÿ ïåðåìåííàÿ
const static float inf = -1000000.0f;
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

std::vector<point_3d> objects;
// êîíñòðóêòîð êëàññà Scene3D
scene_3d::scene_3d(QWidget* parent/*= 0*/) : QGLWidget(parent) 
{    
   xRot = -90; 
   yRot = 0; 
   zRot = 0; 
   zTra = 0; 
   nSca = 1; 
   startTimer(40);
   // ïåðåäàåò äàëüøå óêàçàòåëü íà îáúåêò parent
} 

void scene_3d::initializeGL() // èíèöèàëèçàöèÿ
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


void scene_3d::resizeGL(int w, int h) // îêíî âèäæåòà
{ 
   glViewport(0, 0, w, h);
		double ratio = static_cast<double>(w) / h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2*ratio, 2*ratio, -10, 10, -1.0, 1.0);
		//glFrustum(-ratio, ratio, -2, , 0,1);
		glMatrixMode(GL_MODELVIEW);
}

void scene_3d::paintGL() // ðèñîâàíèå
{       double x,y,z;
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glClearColor(0.0, 0.0, 0.2f, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);		
		glLoadIdentity();	
				
		
		rtri += 1;
		glRotatef(rtri,0.0,0.0,1.0);
		glColor4f(1.0, 0.0, 1,1);
		
		
	for (size_t i = 0; i < objects.size(); i++)
		{
			x = objects[i].x - 1;
			y = objects[i].y - 1;
			z = objects[i].z - 1;			
			glBegin(GL_TRIANGLES);
			   glVertex3f(x,y,z);
			   glVertex3f(x + 1, y + 1,z);
			   glVertex3f(x + 1,y - 1,z);
			glEnd();
			
		}
		swapBuffers();
	objects.resize(0);	
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
