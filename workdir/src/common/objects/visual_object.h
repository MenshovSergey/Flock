#pragma once
#include"object_vis_base.h"
#include<containers/look.h>
#include<geometry/point_3d.h>

namespace object
{

    class visual_object
        : object_vis
    {

    public: //info_vis
        void render     () override;

    public: //semantic
        void update     () override;
        void reg        () override;
        void unreg      () override;
    public: //manipulators
        void move       (point_3d) override;

    public: //construction
        void init       ();
        void deinit     ();
             visual_object ();
             ~visual_object();
    private:
        point_3d coord;
        //quaternion for orientation
        
        look model_vis;
        bool is_visible;

    };
} //object
