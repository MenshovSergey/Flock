#pragma once
#include <objects/object_vis_base.h>
#include <scene/scene_base.h>
#include <scene3d/scene3d.h>
#include "typedef/typedef.h"
namespace scene
{


struct scene
    : public construction
    , public info
    , public semantic
{
    public: //construction
        void add           (boost::shared_ptr<object::object_vis>  );
        void remove        (size_t);

    public: //info
        object::object_vis const &                access  (size_t);
        std::vector<boost::shared_ptr<object::object_vis>> const &  content ();

    public: //semantic
        void update   ();
        void render   ();
        void obj_sort (); //i suppose we would update managers before objects and so on;

        void init (scene_3d & new_master);
             scene();
             ~scene();
    private:
        std::vector<boost::shared_ptr<object::object_vis>>       object_list;
        std::map<boost::shared_ptr<object::object_vis>, boost::shared_ptr<look> > looks;
        size_t                                list_size;
        scene_3d * frame;
		//boost::shared_ptr<scene_3d>                             frame;

};

} //world
