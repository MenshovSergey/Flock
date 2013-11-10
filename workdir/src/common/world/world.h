#pragma once
#include <objects/object_mod_base.h>
#include <scene/scene.h>
#include <world/world_base.h>


namespace world
{


struct world
    : public construction
    , public info
    , public semantic
{
    public: //construction
        void add           (object::object_mod * const) override;
        void remove        (size_t) override;

    public: //info
        object::object_mod *               const access  (size_t) override;
        std::vector<object::object_mod*> & const content () override;

    public: //semantic
        void update   () override;
        void obj_sort () override; //i suppose we would update managers before objects and so on;
        
             world(scene::scene & const);
             ~world();
    private:
        std::vector<object::object_mod*> object_list;
        size_t                           list_size;
        scene::scene &                   visualisation;

};

} //world
