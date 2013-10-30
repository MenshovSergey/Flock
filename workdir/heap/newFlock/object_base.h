#pragma once
#include "state.h"
#include "look.h"
#include <vector>

struct object_base
{
    virtual void  update       () = 0;
    //virtual void  add          () = 0; What was it meant to be?
    virtual void  erase        () = 0;
    virtual void  move         () = 0;
	virtual void  reg_manager  () = 0;
    virtual state get_state    () = 0;
	virtual look  get_look     () = 0;
	virtual       ~object_base () = 0;
};

