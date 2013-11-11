#include<objects/dynamic_object.h>
#include<objects/static_object.h>
#include<objects/visual_object.h>
#include<behaviour/behaviour.h>
#include<management/manager.h>
#include<world/world.h>
#include<scene/scene.h>
#include<scene3d/scene3d.h>
#include<QtWidgets/QApplication>
#include<iostream>
#include<Windows.h>
#include<vector>
#include<map>

using namespace std;



void homing(vector<object::object_mod*>& const objects, map<object::object_mod*, object::controls*>& controls)
{
    size_t size = objects.size();
    point_3d target;
    bool flag = false;
    for (int i = 0; i < size; ++i)
    {
        if ((objects[i]->get_type()) == 257)
        {
            target = objects[i]->get_state().coord;
            flag = true;
        }
    }

    if (flag == false)
    {
        return;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (controls.find(objects[i]) != controls.end())
        {
            state temp = objects[i]->get_state();
            point_3d to_target(target.x - temp.coord.x, target.y - temp.coord.y, target.z - temp.coord.z);
            to_target /= abs(to_target);
            point_3d cur_speed = temp.speed /= abs (temp.speed);
            point_3d new_force = to_target - cur_speed;
            (*controls.find(objects[i])).second->full_force(new_force);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	scene_3d w;
	w.show();
	return a.exec();
}