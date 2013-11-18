#include<geometry/point_3d.h>
#include<behavior/behavior_base.h>
#include<objects/dynamic_object.h>

namespace behavior
{
    class behavior_seek: public behavior_base
    {
        public:
            void apply          (object::dynamic_object * obj) override;
            void init           (point_3d new_target);
                 behavior_seek  (point_3d target);
                 ~behavior_seek ();
        private:
            point_3d target_;

    };

    class behavior_flee: public behavior_base
    {
        public:
            void apply          (object::dynamic_object * obj) override;
            void init           (point_3d new_target);
                 behavior_flee  (point_3d target);
                 ~behavior_flee ();
        private:
            point_3d target_;

    };

} //behavior