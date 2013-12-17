#pragma once
#include<objects/object_mod_base.h>


namespace object
{

    struct manager_base
        : public object_mod
    {
        public:
            virtual   ~manager_base(){};
    };

}