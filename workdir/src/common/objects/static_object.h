#pragma once
#include <geometry/point_3d.h>
#include <objects/object_mod_base.h>
#include <objects/visual_object.h>

namespace object
{

class static_object
    : object_mod
{

    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;

    public: //semantic
        void      update        () override;

    public : //object_mod
        void      reg           (object_mod*) override;
        void      unreg         (object_mod*) override;

    public: 
        void      init          (point_3d, double);
        void      deinit        ();

                  static_object ();
                  ~static_object();
    private:
        point_3d       coord;
        double         radius;
        visual_object* visualisation;
        //quaternion for orientation
};

} //object
