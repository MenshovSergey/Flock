#pragma once
#include "object_base.h"
#include <vector>

class world_base
{
    public:
        virtual void                   update     () = 0;
        virtual void                   add        () = 0;
        virtual void                   remove     () = 0;
        virtual void                   access     () = 0;
        virtual vector<object> & const content    () = 0;
        virtual void                   obj_sort   () = 0; //i suppose we would update managers before objects and so on;
        virtual                        ~world_base() = 0;
};