#pragma once 
#include <objects/object_mod_base.h>
#include <objects/dynamic_object.h>
#include <behaviour/behaviour.h>


namespace object
{

struct flock : public object_mod 
{
    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;
        int       get_type      () override;

    public: //semantic
        void      update        () override;

    public: //object_mod
        void      reg           (object_mod*) override;
        void      unreg         (object_mod*) override;

    public:
        void      add_b         (behaviour::behaviour& new_behavior);
        void      rem_b         ();
                  flock         (int object_type);
                  ~flock        ();

    private:
        std::vector<dynamic_object*>       objects;
        size_t                             o_size;
        std::vector<behaviour::behaviour*> behaviors;
        size_t                             b_size;
        int                                obj_type;
};

}