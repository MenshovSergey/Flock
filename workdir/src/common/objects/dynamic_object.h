#pragma once
#include <objects/object_mod_base.h>
#include <objects/visual_object.h>
#include <geometry/point_3d.h>

namespace object
{

class dynamic_object
    : public object_mod
    , public controls
{
    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;
        int       get_type      () override;

    public: //semantic
        void      update        () override;

    public : //controls
        void      set_force     (point_3d new_force) override;
        void      full_force    (point_3d dir_force) override;

    public : //object_mod
        void      reg           (object_mod*) override;
        void      unreg         (object_mod*) override;


    public:
        void      init          (point_3d, point_3d, point_3d, double, double, double, double);
        void      deinit        ();
        void      revisualise   (visual_object*);

                  dynamic_object(int object_type);
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
        int            obj_type;
        //quaternion for orientation
};

} //object
