#ifndef SPHERE
#define SPHERE

#include <cmath>
#include "shape.h"

class Sphere: public Shape {
    public:
        // get
        float get_radius() const {return this->radius;}

        // set
        void set_radius(float r) {this->radius = r;}
        void set_particle_id(size_t i_pid) {this->particle_id = i_pid;} 

    private:
        float radius = 0.0;
        size_t particle_id = 0;
        
};

#endif