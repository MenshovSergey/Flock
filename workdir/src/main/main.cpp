#include<objects/dynamic_object.h>
#include<objects/static_object.h>
#include<objects/visual_object.h>
#include<behaviour/behaviour.h>
#include<management/manager.h>
#include<world/world.h>
#include<scene/scene.h>
//#include<QtWidgets/QApplication>
#include<iostream>
#include<Windows.h>
#include<vector>
#include<map>

using namespace std;

void gravity_xyz(std::vector<object::object_mod*>& const objects, std::map<object::object_mod*, object::controls*>& controls)
{
    size_t size = objects.size();
    int x_lim = 15;
    int y_lim = 10;
    int z_lim = 10;
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

void homing(std::vector<object::object_mod*>& const objects, std::map<object::object_mod*, object::controls*>& controls)
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
    //QApplication a(argc, argv);
    // TEST CODE!
    scene::scene main_scene;
    world::world universe(main_scene);
    behaviour::behaviour gravity(&gravity_xyz);

    object::manager * gravity_man = new object::manager(0);
    object::dynamic_object * temp = new object::dynamic_object(1);
    object::visual_object * vis = new object::visual_object;

    point_3d t_coord(10,10,10);
    point_3d t_speed(0,5,0);
    point_3d t_force(0,0,0);
    temp->init(t_coord, t_speed, t_force, 100, 0.5, 1, 1);
    temp->revisualise(vis);

    t_coord.x = 30;
    t_coord.y = 30;
    t_coord.z = 10;
    object::static_object * st = new object::static_object(257);
    st->init(t_coord, 1);

    vis->change_vis(true);

    gravity_man->init(homing);
    gravity_man->reg(temp);
    gravity_man->reg(st);

    main_scene.add(vis);
    universe.add(gravity_man);
    universe.add(temp);
    universe.add(st);
    
    for(int i = 0; i < 1000; ++i)
    {
        universe.update();
        main_scene.update();
        main_scene.render();
        //cout << (temp->get_state_vis()).coord.x << " " << (temp->get_state_vis()).coord.y << " " <<(temp->get_state_vis()).coord.z << endl;
        Sleep(150);
    }
    int a;
    cin >> a;
    // ^^ TEST CODE
    return 0;
}