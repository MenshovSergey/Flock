#pragma once
#include "objects/object_mod.h"
#include<geometry/point_3d.h>

namespace object
{

class dynamic_object
    : object_mod
    , controls
{
    public: //construction
        void      init          () override;
        void      deinit        () override;
    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;

    public: //semantic
        void      update        () override;
        void      reg           () override;
        void      unreg         () override;

    public : //controls
        void      set_force     (point_3d new_force) override;


                  dynamic_object();
                 ~dynamic_object();
    private:
        point_3d       coord;
        point_3d       speed;
        point_3d       force;
        double         max_speed;
        double         max_force;
        double         mass;
        double         radius;
        visual_object* visualisation;
        //quaternion for orientation
};

} //object
