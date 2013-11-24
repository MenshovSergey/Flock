#pragma once
#include <objects/object_vis_base.h>
#include <scene/scene_base.h>
#include <scene3d/scene3d.h>

namespace scene
{


struct scene
    : public construction
    , public info
    , public semantic
{
    public: //construction
        void add           (object::object_vis * );
        void remove        (size_t);

    public: //info
        object::object_vis const &                access  (size_t);
        std::vector<object::object_vis*> const &  content ();

    public: //semantic
        void update   ();
        void render   ();
        void obj_sort (); //i suppose we would update managers before objects and so on;

        void init (scene_3d & new_master);
             scene();
             ~scene();
    private:
        std::vector<object::object_vis*>       object_list;
        std::map<object::object_vis *, look *> looks;
        size_t                                list_size;
        scene_3d *                             frame;

};

} //world
