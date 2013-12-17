#pragma once

#include<management/manager_base.h>
#include<flock/flock.h>


namespace object
{

class manager_flocks
    : public manager_base
{

    public: //info_mod
        state     get_state         () override;
        state_vis get_state_vis     () override;
        int       get_type          () override;

    public: //semantic
        void      update            () override;

    public : //object_mod
        void      reg               (boost::shared_ptr<object_mod>) override;
        void      unreg             (boost::shared_ptr<object_mod>) override;
        void      reg_f             (boost::shared_ptr<flock>);

                  manager_flocks (int object_type);
                  ~manager_flocks();
        void      init           (double radius);
        void      deinit         ();

    private:
         double radius;
         int    obj_type;
         std::vector<boost::shared_ptr<flock> >          flocks;
         std::vector<boost::shared_ptr<object_mod> > objects;

};

}//object