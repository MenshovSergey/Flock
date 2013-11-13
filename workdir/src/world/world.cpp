#include<world/world.h>
#include<cassert>
#include<iostream>

using namespace std;
namespace world
{
    void world::add(object::object_mod * const new_obj)
    {
        object_list.push_back(new_obj);
        ++list_size;
    }

    void world::remove(size_t obj_id)
    {
        object_list.pop_back(); //TODO: remove object by id
        --list_size;
    }

    object::object_mod const * world::access  (size_t obj_id)
    {
        assert((0 <= obj_id) && (obj_id < list_size));
        return object_list[obj_id];
    }

    vector<object::object_mod*> const & world::content()
    {
        return object_list;
    }

    void world::update()
    {
        for (size_t i = 0; i < list_size; ++i)
        {
            object_list[i]->update();
        }
    }

    void world::obj_sort()
    {
        assert(0); //TODO: sort objects
    }

    world::world(scene::scene &  new_visualisation)
        : object_list(0)
        , list_size(0)
        , visualisation(new_visualisation)
    {
    }

    world::~world()
    {
        for (int i = 0; i < list_size; ++i)
        {
            delete(object_list[i]);
        }
        delete(&visualisation);
    }

} //world