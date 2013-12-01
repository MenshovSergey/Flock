#include <behavior/behavior_base.h>
#include <geometry/point_3d.h>
#include <objects/dynamic_object.h>

namespace behavior
{
    
    class behavior_pursuit: public behavior_base
    {
        public:
            void apply             (boost::shared_ptr<object::dynamic_object>  obj) override;
                 
                 behavior_pursuit  (boost::shared_ptr<object::object_mod>  target);
                 ~behavior_pursuit ();
        private:
            boost::shared_ptr<object::object_mod>  target_;

    };

    class behavior_evade: public behavior_base
    {
        public:
            void apply             (boost::shared_ptr<object::dynamic_object>  obj) override;
                 
                 behavior_evade  (boost::shared_ptr<object::object_mod>  target);
                 ~behavior_evade ();
        private:
            boost::shared_ptr<object::object_mod>  target_;

    };

    point_3d interpolation(boost::shared_ptr<object::object_mod>  target, boost::shared_ptr<object::dynamic_object> obj);
} //behavior