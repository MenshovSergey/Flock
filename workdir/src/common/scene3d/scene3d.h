#pragma once

#include<containers/look.h>

//#include <qopengl.h>
#include <QGLWidget>
#include <QtGui> 

#include <QGLWidget>
#include <gl\GLU.h>
#include <qtimer.h>

//using namespace std;
// ïîäêëþ÷àåì êëàññ QGLWidget

class scene_3d : public QGLWidget // êëàññ Scene3D íàñëåäóåò âñòðîåííûé êëàññ QGLWidget
{ 
   private: 
      GLfloat xRot; // ïåðåìåííàÿ õðàíèò óãîë ïîâîðîòà âîêðóã îñè X
      GLfloat yRot; // ïåðåìåííàÿ õðàíèò óãîë ïîâîðîòà âîêðóã îñè Y   
      GLfloat zRot; // ïåðåìåííàÿ õðàíèò óãîë ïîâîðîòà âîêðóã îñè Z
      GLfloat zTra; // ïåðåìåííàÿ õðàíèò âåëè÷èíó òðàíñëÿöèè îñè Z 
      GLfloat nSca; // ïåðåìåííàÿ îòâå÷àåò çà ìàñøòàáèðîâàíèå îáúåêòà
      
      
      
      
        
   protected:
      // ìåòîä äëÿ ïðîâåäåíèÿ èíèöèàëèçàöèé, ñâÿçàííûõ ñ OpenGL 
      /*virtual*/ void initializeGL();         
      // ìåòîä âûçûâàåòñÿ ïðè èçìåíåíèè ðàçìåðîâ îêíà âèäæåòà            
      /*virtual*/ void resizeGL(int nWidth, int nHeight);  
      // ìåòîä, ÷òîáû çàíîâî ïåðåðèñîâàòü ñîäåðæèìîå âèäæåòà  
      /*virtual*/ void paintGL(); 
	  
       
            
      
   public: 
      scene_3d(QWidget* parent = 0);	
	
	  void drawFish(look fish_look);
	  void timerEvent(QTimerEvent * event);
	  void deleteFish(int number);
}; 
