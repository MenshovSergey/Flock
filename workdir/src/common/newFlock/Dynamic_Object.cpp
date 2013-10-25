#include "Object.h"
#include "DynamicObject.h"
#include "cstdlib"

inline int qrand (int x)
{
    return rand() % x;
}

using namespace std;
Dynamic_Object::Dynamic_Object(){
   x = 0;
   y = 0;
   z = 0;
}
void Dynamic_Object ::add(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
void Dynamic_Object ::update(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
void Dynamic_Object ::erase(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
void Dynamic_Object ::move(){
    x = qrand(1000);
    y = qrand(340);
    z = qrand(700);
}
