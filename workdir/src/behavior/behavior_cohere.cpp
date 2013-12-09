#include <behavior/behavior_cohere.h>


using namespace std;
 namespace behavior
 {
    void behavior_cohere::apply (boost::shared_ptr<object::dynamic_object> obj)
    {
        size_t size = mates_.size();
        point_3d temp;
        
        for (size_t i = 0; i < size; ++i)
        {
            if (obj != mates_[i])
            {
                point_3d v = (obj->get_state()).coord - (mates_[i]->get_state()).coord;
                double r = abs(v);
                double b = b_ + b_ * 0.5 * sin(r);
                temp += v / r * (1 / (r * r * r) - 1 / r * b * b) * a_;
            }
        }
        obj->add_force(temp);
    }

    void behavior_cohere::init (vector<boost::shared_ptr<object::object_mod> > const& mates)
    {
        mates_ = mates;
    }

    void behavior_cohere::init (double optimal_radius, double power)
    {
        b_ = 1 / optimal_radius;
        a_ = power;
    }


    behavior_cohere::behavior_cohere  (double optimal_radius, double power)
        : mates_(0)
        , a_(power)
        , b_(1 / optimal_radius)
    {
    }
     behavior_cohere::~behavior_cohere ()
     {
     }

 }

