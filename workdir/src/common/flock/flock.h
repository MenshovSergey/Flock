#pragma once
#include <objects/object_mod_base.h>
#include <objects/dynamic_object.h>
#include <behavior/behavior.h>


namespace object
{

struct flock : public object_mod
{
    public: //info_mod
        state               get_state     () override;
        state_vis           get_state_vis () override;
        int                 get_type      () override;

    public: //semantic
        void                update        () override;

    public: //object_mod
        void                reg           (boost::shared_ptr<object_mod>) override;
        void                unreg         (boost::shared_ptr<object_mod>) override;

    public:
        std::vector<boost::shared_ptr<object_mod>> get_members   ();
        void                add_b         (boost::shared_ptr<behavior::behavior_base> new_behavior);
        void                rem_b         ();
                            flock         (int object_type);
                            ~flock        ();

    private:
        std::vector<boost::shared_ptr<dynamic_object>>          objects;
        size_t                                o_size;
        std::vector<boost::shared_ptr<behavior::behavior_base>> behaviors;
        size_t                                b_size;
        int                                   obj_type;
};

}
