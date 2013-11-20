#include <behavior/behavior_base.h>
#include <geometry/point_3d.h>
#include <objects/dynamic_object.h>

namespace behavior
{
    
    class behavior_offset: public behavior_base
    {
        public:
            void apply             (object::dynamic_object * obj) override;
            void init              (double new_offset);
                 
                 behavior_pursuit  (object::object_mod * target);
                 behavior_pursuit  (object::object_mod * target, double offset);
                 ~behavior_pursuit ();
        private:
            object::object_mod * target_;
            double offset_;

    };

    point_3d interpolation(object::object_mod * target, object::dynamic_object * obj);
} //behavior