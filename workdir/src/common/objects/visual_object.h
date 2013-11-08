#pragma once
#include<objects/object_vis_base.h>
#include<objects/object_mod_base.h>
#include<containers/look.h>
#include<geometry/point_3d.h>

namespace object
{

    class visual_object
        : object_vis
    {

    public: //info_vis
        void render        () override;

    public: //semantic
        void update        () override;

    public: //manipulators
        void move          (point_3d) override;

    public: //construction
        void init          (point_3d);
        void deinit        ();
        void giveown       (object_mod * const);
             visual_object ();
             ~visual_object();
    private:
        point_3d coord;
        //quaternion for orientation
        
        object_mod * owner;
        look model_vis;
        bool is_visible;

    };
} //object
