#pragma once
#include <geometry/point_3d.h>
#include <objects/object_mod_base.h>
#include <objects/visual_object.h>

namespace object
{

class static_object
    : public object_mod
{

    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;
        int       get_type      () override;

    public: //semantic
        void      update        () override;

    public : //object_mod
        void      reg           (boost::shared_ptr<object_mod>) ;
        void      unreg         (boost::shared_ptr<object_mod>) ;

    public: 
        void      init          (point_3d, double);
        void      deinit        ();

                  static_object (int object_type);
                  ~static_object();
    private:
        point_3d       coord;
        double         radius;
        boost::shared_ptr<visual_object> visualisation;
        int            obj_type;
        //quaternion for orientation
};

} //object
