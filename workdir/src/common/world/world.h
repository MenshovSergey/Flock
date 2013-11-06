#pragma once
#include <objects/object_mod_base.h>
#include <scene/scene.h>
#include <world/world_base.h>


namespace world
{


struct world
    : construction
    , info
    , semantic
{
    public: //construction
        void add           ();
        void remove        ();

    public: //info
        object::object_mod &               const access  ();
        std::vector<object::object_mod*> & const content ();

    public: //semantic
        void update   ();
        void obj_sort (); //i suppose we would update managers before objects and so on;
        
             world();
             ~world();
    private:
        std::vector<object::object_mod*> object_list;
        size_t                           list_size;
        scene::scene &                   visualisation;

};

} //world
