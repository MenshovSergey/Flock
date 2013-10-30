#pragma once

class scene_base
{
    public:
        virtual void update     () = 0;
        virtual void render     () = 0;
        virtual void add        () = 0;
        virtual void remove     () = 0;
        virtual      ~scene_base() = 0;
};