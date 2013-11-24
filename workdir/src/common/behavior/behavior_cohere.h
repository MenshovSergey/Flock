#include<behavior/behavior_base.h>
#include<geometry/point_3d.h>
#include<objects/object_mod_base.h>

namespace behavior
{
    class behavior_cohere: public behavior_base
    {
        public:
            void apply           (object::dynamic_object * obj) override;
            void init            (std::vector<object::object_mod *> const & mates);
                 behavior_cohere  (double optimal_radius, double power);
                 ~behavior_cohere ();
        private:
            std::vector<object::object_mod *> mates_;
            double a_;
            double b_;

    };


} //behavior

