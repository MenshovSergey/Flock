#pragma once
#include <objects/object_vis_base.h>
#include <scene/scene_base.h>

namespace scene
{


struct scene
    : construction
    , info
    , semantic
{
    public: //construction
        void add           ();
        void remove        ();

    public: //info
        object::object_vis &               const access  ();
        std::vector<object::object_vis*> & const content ();

    public: //semantic
        void update   ();
        void obj_sort (); //i suppose we would update managers before objects and so on;
        
             scene();
             ~scene();
    private:
        std::vector<object::object_vis*> object_list;
        size_t                           list_size;

};

} //world
