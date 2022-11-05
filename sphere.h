#ifndef SPHERE
#define SPHERE

#include <cmath>
#include "shape.h"

class Sphere: public Shape {
    public:
        // get
        float get_diameter() const {return 2 * this->radius;}
        float get_radius() const {return this->radius;}
        float get_volume() const {return 4 * M_PI * this->radius * this->radius;}

        // set
        void set_radius(float r) {this->radius = r;}

    private:
        float radius = 0.0;
};

#endif