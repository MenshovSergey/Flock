#pragma once
#include<objects/object_vis_base.h>
#include<objects/object_mod_base.h>
#include<containers/look.h>
#include<geometry/point_3d.h>

namespace object
{

    class visual_object
        : public object_vis
    {

    public: //info_vis
        look render        () override;

    public: //semantic
        void update        () override;

    public: //manipulators
        void move          (point_3d) override;

    public: //construction
        void init          (point_3d);
        void deinit        ();
        void change_vis    (bool);
        void change_rot    (bool);
        //void giveown       (boost::shared_ptr<object_mod> const);
		void giveown       (object_mod * const);
             visual_object (look new_model);
             ~visual_object();
    private:
        point_3d coord;
        //quaternion for orientation
        double phi;
		double psi;
        //boost::shared_ptr<object_mod>  owner;
		object_mod * owner;
        look model_vis;
        bool is_visible;
        bool is_rotating;
    };
} //object
