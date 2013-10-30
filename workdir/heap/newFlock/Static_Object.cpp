#include "StaticObject.h"
#include "random"
#include "iostream"
#include "vector"
#include "my.h"
using namespace std;

inline int qrand (int x)
{
    return rand() % x;
}

Static_Object::Static_Object(){
   x = 0;
   y = 0;
   z = 0;
}
void Static_Object ::add(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
    //objects.push_back(this);
    My::add(this);

    //cout <<objects.size();
}
void Static_Object ::update(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
void Static_Object ::erase(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
void Static_Object ::move(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
int Static_Object::getX(){
    return x;
}
int Static_Object::getY(){
    return y;
}


