#ifndef SPHERE
#define SPHERE

#include "shape.h"

class Sphere {
    public:
        // get
        float get_diameter() const {return this->diameter;}
        float get_radius() const {return this->radius;}

        // set
        void set_radius(float r) {this->radius = r;}

    private:
        float diameter = 2 * radius;
        float radius = 0.0;
};

#endif