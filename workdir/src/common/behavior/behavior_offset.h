#include <behavior/behavior_base.h>
#include <geometry/point_3d.h>
#include <objects/dynamic_object.h>

namespace behavior
{
    
    class behavior_offset: public behavior_base
    {
        public:
            void apply             (boost::shared_ptr<object::dynamic_object>  obj) override;
            void init              (double new_offset);
                 
                 behavior_offset  (boost::shared_ptr<object::object_mod>  target);
                 behavior_offset  (boost::shared_ptr<object::object_mod>  target, double offset);
                 ~behavior_offset ();
        private:
            boost::shared_ptr<object::object_mod>  target_;
            double offset_;

    };

    point_3d interpolation(boost::shared_ptr<object::object_mod>  target, boost::shared_ptr<object::dynamic_object>  obj);
} //behavior