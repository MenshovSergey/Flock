#pragma once
#include <objects/object_mod_base.h>
#include <objects/object_base.h>
#include <flock/flock.h>
#include <behavior/behavior.h>
#include <vector>
#include <map>

namespace object
{

struct manager 
    : public object_mod
{
    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;
        int       get_type      () override;

    public: //semantic
        void      update        () override;

    public: //object_mod
        void      reg           (boost::shared_ptr<object_mod>) ;
        void      unreg         (boost::shared_ptr<object_mod>) ;

    public:
        void      init          (behavior::behavior_old new_behaviour);
        void      deinit        ();
                  manager       (int object_type);
                  ~manager      ();

    private:
        std::vector <boost::shared_ptr<object_mod>>         registered;
        std::map<boost::shared_ptr<object_mod>, boost::shared_ptr<controls>> controlled;
        size_t                           reg_size;
        size_t                           cont_size;
        behavior::behavior_old           b_func;
        int                              obj_type;
};

} //object