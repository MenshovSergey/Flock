#include<objects/dynamic_object.h>
#include<objects/static_object.h>
#include<objects/visual_object.h>
#include<behavior/behavior.h>
#include<management/manager.h>
#include<world/world.h>
#include<scene/scene.h>
#include<scene3d/scene3d.h>

using namespace std;




/*void homing(vector<object::object_mod*> const &  objects, map<object::object_mod*, object::controls*>& controls)
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
}*/

/////
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

struct test_i
{
    virtual double get() const = 0;
    virtual ~test_i() 
    {
        int i = 0;
    }
};

typedef boost::shared_ptr<test_i> test_i_ptr;

struct test_ii
{
    virtual void update() = 0;
    virtual ~test_ii() {}
};

typedef boost::shared_ptr<test_ii> test_ii_ptr;


struct test_obj: test_i, test_ii
{
    test_obj( double o )
        : p_(o)
    {}


// test_i
private:
    double get() const override
    {
        return p_;
    }

// test_ii
private:
    void update() override {}

private:
    double p_;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scene_3d w;
    w.show();


/*    std::vector<test_i_ptr> test_;

    test_.push_back(boost::make_shared<test_obj>(6));


    test_i_ptr i_ptr = test_.front();

    i_ptr->get();
          
//    test_i * i = &*i_ptr;

    test_ii_ptr ii_ptr = boost::dynamic_pointer_cast<test_ii>(i_ptr);

    ii_ptr->update();
    */



    test_i * A = new test_obj(8);
    delete A;



    return a.exec();
}