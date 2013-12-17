#pragma once

#include<managers/manager_base.h>


namespace object
{

class manager_collision
    : public manager_base
{

    public: //info_mod
        state     get_state     () override;
        state_vis get_state_vis () override;
        int       get_type      () override;

    public: //semantic
        void      update        () override;

    public : //object_mod
        void      reg           (boost::shared_ptr<object_mod>) ;
        void      unreg         (boost::shared_ptr<object_mod>) ;


                  manager_collision ();
                  manager_collision (double ratio, double force);
        void      init              (double ratio, double force);

    private:
         double r_ratio;
         double force;
}

}//object