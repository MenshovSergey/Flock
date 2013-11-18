#include <behavior/behavior_base.h>
#include <geometry/point_3d.h>
#include <objects/dynamic_object.h>

namespace behavior
{
    
    class behavior_pursuit: public behavior_base
    {
        public:
            void apply             (object::dynamic_object * obj) override;
                 
                 behavior_pursuit  (object::object_mod * target);
                 ~behavior_pursuit ();
        private:
            object::object_mod * target_;

    };

    class behavior_evade: public behavior_base
    {
        public:
            void apply             (object::dynamic_object * obj) override;
                 
                 behavior_evade  (object::object_mod * target);
                 ~behavior_evade ();
        private:
            object::object_mod * target_;

    };

    point_3d interpolation(object::object_mod * target, object::dynamic_object * obj);
} //behavior