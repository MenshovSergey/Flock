#pragma once
#include <objects/object_mod_base.h>
#include <geometry/point_3d.h>

namespace object
{

class static_object
    : object_mod
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

                  static_object ();
                  ~static_object();
    private:
        point_3d       coord;
        double         radius;
        visual_object* visualisation;
        //quaternion for orientation
};

} //object
