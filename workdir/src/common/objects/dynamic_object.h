#pragma once
#include <objects/object_mod_base.h>
#include <objects/visual_object.h>
#include <geometry/point_3d.h>

namespace object
{

struct flock;

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
		void      add_force     (point_3d new_force) override;
        void      full_force    (point_3d dir_force) override;

    public : //object_mod
        void      reg           (boost::shared_ptr<object_mod>) override;
        void      unreg         (boost::shared_ptr<object_mod>) override;


    public:
        void      init          (point_3d, point_3d, point_3d, double, double, double, double, double);
        void      deinit        ();
        void      revisualise   (boost::shared_ptr<visual_object>);
        void      set_flock     (flock * new_parent);
        flock *   parent_flock  ();

                  dynamic_object(int object_type);
                  ~dynamic_object();

    private:
        point_3d       coord;
        point_3d       speed;
        point_3d       force;
        double         max_speed;
        double         max_force;
        double         max_rot;
        double         rot_phi;
        double         rot_psi;
        double         phi;
        double         psi;
        double         mass;
        double         radius;
		void           truncate_force();
        boost::shared_ptr<visual_object> visualisation;
        flock *        parent;
		//visual_object * visualisation;
        int            obj_type;
        //quaternion for orientation


        point_3d prev_force;
};

} //object
