#pragma once

#include<management/manager_base.h>


namespace object
{

class manager_avoidance
    : public manager_base
{

    public: //info_mod
        state     get_state         () override;
        state_vis get_state_vis     () override;
        int       get_type          () override;

    public: //semantic
        void      update            () override;

    public : //object_mod
        void      reg               (boost::shared_ptr<object_mod>) ;
        void      unreg             (boost::shared_ptr<object_mod>) ;


                  manager_avoidance ();
                  manager_avoidance (double radius);
        void      init              (double radius);

    private:
        double    radius;

}

}//object