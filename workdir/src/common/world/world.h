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
        void add           (boost::shared_ptr<object::object_mod> ) ;
        void remove        (size_t) override;

    public: //info
       boost::shared_ptr<object::object_mod> const                 access  (size_t) ;
        std::vector<myPtr<object::object_mod>::my_ptr> const &  content () ;

    public: //semantic
        void update   () override;
        void obj_sort () override; //i suppose we would update managers before objects and so on;
        
             world(scene::scene & );
             ~world();
    private:
        std::vector<boost::shared_ptr<object::object_mod>> object_list;
        size_t                           list_size;
        scene::scene &                   visualisation;

};

} //world
