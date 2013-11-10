#include <geometry/point_3d.h>
#include <scene3d/scene3d.h>

#include <QtGui>      // ïîäêëþ÷àåì ìîäóëü QtGui
//#include <QtCore>     // ïîäêëþ÷àåì ìîäóëü QtCore
//#include <QtOpenGL>   // ïîäêëþ÷àåì ìîäóëü QtOpenGL
#include <qmath.h>     // ïîäêëþ÷àåì ìàòåìàòè÷åñêóþ áèáëèîòåêó
#include <vector>

const static float pi=3.141593, k=pi/180; // ãëîáàëüíàÿ ïåðåìåííàÿ
const static float inf = -1000000.0;
double rtri = 0;

point_3d p(0,0,0);

point_3d rotate(point_3d a,double angle)
{
	point_3d b(0,0,0);
	b.z = a.z;
	b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) +a.y * cos(angle);
	 return b;
}

vector<point_3d> objects;
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
	    glClearColor(0.0, 0.0, 0.2, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);		
		glLoadIdentity();	
				
		
		rtri += 1;
		glRotatef(rtri,0.0,0.0,1.0);
		glColor4f(1.0, 0.0, 1,1);
		
		
	for (int i = 0; i < objects.size(); i++)
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
		updateGL();
	}
void scene_3d::drawFish(look fish_look)
{
	  objects.push_back(fish_look.coord);
 
	//updateGL();
}
