#include<objects/dynamic_object.h>
#include<objects/static_object.h>
#include<objects/visual_object.h>
#include<behavior/behavior.h>
#include<management/manager.h>
#include<world/world.h>
#include<scene/scene.h>
#include<scene3d/scene3d.h>
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scene_3d w;
    w.show();
	
    return a.exec();
	
}