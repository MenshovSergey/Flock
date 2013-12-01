#include<behavior/behavior_base.h>
#include<geometry/point_3d.h>
#include<objects/object_mod_base.h>


#include "typedef/typedef.h"






namespace behavior
{
    class behavior_cohere: public behavior_base
    {
        public:
            void apply           (boost::shared_ptr<object::dynamic_object> obj)  ;
            void init            (std::vector<boost::shared_ptr<object::object_mod> > const&);
                 behavior_cohere  (double optimal_radius, double power);
                 ~behavior_cohere ();
        private:
            std::vector<boost::shared_ptr<object::object_mod>> mates_;
            double a_;
            double b_;

    };


} //behavior

