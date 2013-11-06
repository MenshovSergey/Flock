#pragma once
#include <objects/object_mod_base.h>
#include <objects/object_base.h>
#include <flock/flock.h>
#include <behaviour/behaviour.h>
#include <vector>

namespace object
{

struct manager 
    : object_mod
{
	public: //construction
        void      init          () override;
        void      deinit        () override;
    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;

    public: //semantic
        void      update        () override;
        void      reg           () override;
        void      unreg         () override;

                  manager       ();
                  ~manager      ();

    private:
        std::vector<object_mod*> registered;
        std::vector<controls*>   controlled;
        size_t                   reg_size;
        size_t                   cont_size;
        behaviour                b_func;
};

} //object