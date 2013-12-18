#include<objects/dynamic_object.h>
#include<objects/static_object.h>
#include<objects/visual_object.h>
#include<behavior/behavior_cohere.h>
#include<behavior/behavior_pursuit.h>
#include<behavior/behavior.h>
#include<management/manager_flocks.h>
#include<world/world.h>
#include<scene/scene.h>
#include<scene3d/scene3d.h>
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

using namespace std;

double target_speed = 0.5;

int new_flock_id;
bool lock_screen = false;
bool fix_run = true;
scene_3d * frame;

look prototype_look;
TwBar * control_bar;
scene::scene main_scene;
world::world universe(main_scene);
point_3d t_center;

vector<boost::shared_ptr<object::dynamic_object> > temps;
vector<boost::shared_ptr<object::visual_object> > viss;

boost::shared_ptr<object::dynamic_object> target;
//boost::shared_ptr<object::visual_object> center_vis;

boost::shared_ptr<object::dynamic_object> target2;

boost::shared_ptr<object::manager_flocks> manager = boost::make_shared<object::manager_flocks>(3);

vector<boost::shared_ptr<object::flock> > all_flocks;
point_3d p(0,0,0);

int time_global = 0;
double freq_global = 500;
boost::shared_ptr<behavior::behavior_cohere>  flocker;
boost::shared_ptr<behavior::behavior_cohere>  flocker2;

namespace
{

    void TW_CALL ex_callback(void * clientData)
    { 
        target_speed ++;
    }

     void TW_CALL add_obj(void * clientData)
    { 
        int num = reinterpret_cast<int>(clientData);
        boost::shared_ptr<object::dynamic_object> new_obj = boost::make_shared<object::dynamic_object>(0);
        boost::shared_ptr<object::visual_object> new_vis = boost::make_shared< object::visual_object>(prototype_look);
        point_3d temp(0,0,0.1);
        new_obj->init(temp, temp, temp, 0.5, 1, 0.01, 1, 1);
	    new_obj->revisualise(new_vis);
	    new_vis->change_vis(true);
        all_flocks[num]->reg(new_obj);
	    main_scene.add(new_vis);
	    universe.add(new_obj);
    }

    void TW_CALL add_flock(void * clientData)
    { 
        all_flocks.push_back(boost::make_shared<object::flock>(new_flock_id));
        universe.add(all_flocks[all_flocks.size() - 1] );

        TwAddButton(control_bar, "flock_name", NULL, NULL, " label='Flock'");
        TwAddButton(control_bar, "add_obj", add_obj, reinterpret_cast<void*>(all_flocks.size() - 1), " label='Add Object'");
    }
    //TwAddButton(bar, "Run", RunCB, NULL, " label='Run Forest' ");
} //anonymous

struct Timer_scene :public  QGLWidget
{
 
 
    Timer_scene(QWidget* parent= 0) : QGLWidget(parent)
    {   
        startTimer(40);
    }

    void timerEvent(QTimerEvent * event)
    {   
        if (fix_run) return;

        int posic = 200;
        //flocker->init(25 + 20 * sin(2 * M_PI * time_global / freq_global), 1);
        ++time_global;
        state_vis temp = target->get_state_vis();
        point_3d temp_force(target_speed * (cos(temp.coord.y) - 0.5 *temp.coord.x/posic), 0.9 * target_speed * (cos(temp.coord.z) - 0.5 *temp.coord.y/posic), target_speed * (cos(temp.coord.x) - 0.5 * temp.coord.z/posic));


        //point_3d temp_force(0,0,0);
        target->set_force(temp_force);

        temp_force.x =  target_speed * (cos(temp.coord.y) - 0.5 *temp.coord.x/posic);
        temp_force.y =  target_speed * (cos(temp.coord.z) - 0.5 *temp.coord.y/posic);
        temp_force.z = - 0.9 * target_speed * (cos(temp.coord.x) - 0.5 * temp.coord.z/posic); 

        target2->set_force(temp_force);

        t_center = all_flocks[0]->get_state_vis().coord;

        //center_vis->move(all_flocks[1]->get_state_vis().coord);
        if (lock_screen) 
        {
            frame->center = t_center;
        }
        else
        {
            frame->center = p;
        }
        universe.update();
        main_scene.update();
        main_scene.render();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scene_3d w;
    frame = &w;

    w.show();
    Timer_scene t; 

    main_scene.init(w); //DONEEEEEEEEEEEEEEEEEEEE

    prototype_look.v1.y = -0.5;
    prototype_look.v2.y = 0.5;
    prototype_look.v3.x = 3.;
    prototype_look.v4.z = 0.5;

    TwInit(TW_OPENGL, NULL);

    // Create a tweak bar
    control_bar = TwNewBar("TweakBar");
    TwAddVarRW(control_bar, "target_speed", TW_TYPE_DOUBLE, &target_speed, 
               " label='Target speed' help='' ");

    TwAddVarRW(control_bar, "add_flock_id", TW_TYPE_INT32, &new_flock_id, 
               " label='NewFlock ID' help='ID for flock you create' ");

    TwAddButton(control_bar, "add_flock_main", add_flock, NULL, " label='Add flock'");
    TwAddVarRW(control_bar, "lock_screen", TW_TYPE_BOOL32, &fix_run, " label='Stop/Run'");
    TwAddVarRW(control_bar, "lock_on_flock", TW_TYPE_BOOL32, &lock_screen, " label='Lock on'");

    TwAddButton(control_bar, "text_new_look", NULL, NULL, " label='Protoype look:'");
    TwAddVarRW(control_bar, "prototype_vis", TW_TYPE_BOOL32, &prototype_look.is_visible, 
               " label='Is_visible' help='' ");
    TwAddVarRW(control_bar, "prototype_color_r", TW_TYPE_DOUBLE, &prototype_look.color.x, 
               " label='Color R' help='none' ");
    TwAddVarRW(control_bar, "prototype_color_g", TW_TYPE_DOUBLE, &prototype_look.color.y, 
               " label='Color G' help='none' ");
    TwAddVarRW(control_bar, "prototype_color_b", TW_TYPE_DOUBLE, &prototype_look.color.z, 
               " label='Color B' help='none' ");
    TwAddVarRW(control_bar, "prototype_v1_x", TW_TYPE_DOUBLE, &prototype_look.v1.x, 
               " label='v1.x' help='none' ");
    TwAddVarRW(control_bar, "prototype_v1_y", TW_TYPE_DOUBLE, &prototype_look.v1.y, 
               " label='v1.y' help='none' ");
    TwAddVarRW(control_bar, "prototype_v1_z", TW_TYPE_DOUBLE, &prototype_look.v1.z, 
               " label='v1.z' help='none' ");
    TwAddVarRW(control_bar, "prototype_v2_x", TW_TYPE_DOUBLE, &prototype_look.v2.x, 
               " label='v2.x' help='none' ");
    TwAddVarRW(control_bar, "prototype_v2_y", TW_TYPE_DOUBLE, &prototype_look.v2.y, 
               " label='v2.y' help='none' ");
    TwAddVarRW(control_bar, "prototype_v2_z", TW_TYPE_DOUBLE, &prototype_look.v2.z, 
               " label='v2.z' help='none' ");
    TwAddVarRW(control_bar, "prototype_v3_x", TW_TYPE_DOUBLE, &prototype_look.v3.x, 
               " label='v3.x' help='none' ");
    TwAddVarRW(control_bar, "prototype_v3_y", TW_TYPE_DOUBLE, &prototype_look.v3.y, 
               " label='v3.y' help='none' ");
    TwAddVarRW(control_bar, "prototype_v3_z", TW_TYPE_DOUBLE, &prototype_look.v3.z, 
               " label='v3.z' help='none' ");
    TwAddVarRW(control_bar, "prototype_v4_x", TW_TYPE_DOUBLE, &prototype_look.v4.x, 
               " label='v4.x' help='none' ");
    TwAddVarRW(control_bar, "prototype_v4_y", TW_TYPE_DOUBLE, &prototype_look.v4.y, 
               " label='v4.y' help='none' ");
    TwAddVarRW(control_bar, "prototype_v4_z", TW_TYPE_DOUBLE, &prototype_look.v4.z, 
               " label='v4.z' help='none' ");

    point_3d t_speed(0,0,0);
    point_3d t_force(0,0,0);

	temps.resize(100);
	viss.resize(100);

	flocker = boost::make_shared< behavior::behavior_cohere>(7., 2);
    flocker2 = boost::make_shared< behavior::behavior_cohere>(7., 2);

    all_flocks.push_back(boost::make_shared<object::flock>(2));
    all_flocks.push_back(boost::make_shared<object::flock>(3));

    for (size_t i = 0; i < all_flocks.size(); ++ i)
    {
        universe.add(all_flocks[i]);
        manager->reg_f(all_flocks[i]);
    }

    look model_vis = prototype_look;

   
    model_vis.color.x = 0.9;
    model_vis.color.y = 0.3;
    model_vis.color.z = 0.6;
    
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
	
    model_vis_target.color.x = 1;
    model_vis_target.color.y = 0;
    model_vis_target.color.z = 0;


    boost::shared_ptr<object::visual_object>  target_vis;
    boost::shared_ptr<object::visual_object>  target_vis2;
	
	target = boost::make_shared<object::dynamic_object>(19);
    target_vis = boost::make_shared< object::visual_object>(model_vis_target);

    model_vis_target.color.x = 0;
    model_vis_target.color.y = 1;

    target2 = boost::make_shared<object::dynamic_object>(20);
    target_vis2 = boost::make_shared< object::visual_object>(model_vis_target);

    //center_vis = boost::make_shared< object::visual_object>(model_vis_target);
	boost::shared_ptr<behavior::behavior_pursuit>  seeker = boost::make_shared <behavior::behavior_pursuit>(target);
    boost::shared_ptr<behavior::behavior_pursuit>  seeker2 = boost::make_shared <behavior::behavior_pursuit>(target2);


	point_3d target_pos(0, 0, 0);
    point_3d point_null(0, 0, 0);

	target->init(target_pos, point_null, point_null, 4, 1, 0.01, 1, 1);
	target->revisualise(target_vis);
	//target_vis->change_vis(true);
    target_vis->change_rot(false);
	main_scene.add(target_vis);

    target2->init(target_pos, point_null, point_null, 4, 1, 0.01, 1, 1);
	target2->revisualise(target_vis2);
	//target_vis2->change_vis(true);
    target_vis2->change_rot(false);
	main_scene.add(target_vis2);

	universe.add(target);

    universe.add(target2);

	all_flocks[0]->add_b(flocker);
	all_flocks[0]->add_b(seeker);  

    all_flocks[1]->add_b(flocker2);
	all_flocks[1]->add_b(seeker2);
    
    universe.add(manager);

	for (int i = 0; i < 50; ++i)
	{
		temps[i] = boost::make_shared< object::dynamic_object>(0);
		viss[i] = boost::make_shared< object::visual_object>(model_vis);

		point_3d t_coord(i,sin(static_cast<double>(i)),cos(static_cast<double>(i)));
        temps[i]->init(t_coord, t_speed, t_force, 1, 0.3, 0.05, 1, 1);
        temps[i]->revisualise(viss[i]);
		viss[i]->change_vis(true);
		all_flocks[0]->reg(temps[i]);
        manager->reg(temps[i]);
		main_scene.add(viss[i]);
        universe.add(temps[i]);

	}

    look model_vis_2 = model_vis;
    model_vis_2.color.x = 0.5;
    model_vis_2.color.y = 1;
    model_vis_2.color.z = 0.5;

    for (int i = 50; i < 100; ++i)
	{
		temps[i] = boost::make_shared< object::dynamic_object>(1);
		viss[i] = boost::make_shared< object::visual_object>(model_vis_2);

		point_3d t_coord(-i + 40,sin(static_cast<double>(i)) + 10,cos(static_cast<double>(i)));
        temps[i]->init(t_coord, t_speed, t_force, 1, 0.3, 0.05, 1, 1);
        temps[i]->revisualise(viss[i]);
		viss[i]->change_vis(true);
		all_flocks[1]->reg(temps[i]);
        manager->reg(temps[i]);
		main_scene.add(viss[i]);
        universe.add(temps[i]);

	}

    flocker->init(all_flocks[0]->get_members());
    flocker2->init(all_flocks[1]->get_members());

    universe.update();
    main_scene.update();
    main_scene.render();

    return a.exec();
 
}
