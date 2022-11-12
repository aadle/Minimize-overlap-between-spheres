#ifndef SPACE
#define SPACE

#include <math.h>
#include <vector>

#include "sphere.h"

class Space {
    public:
        void input(std::istream* source);  // read from *source
        // sets the volume of a unit cell
        void set_axis_length(float length[3]);

        int get_N() const {return this->num_spheres;}
        std::vector<Sphere> get_spheres() {return this->Spheres;}

        long count_collisions();

    private:
        int num_spheres = 0;  // totlal number of spheres
        float volume = 0.0;
        double axis_length[3];
        std::vector<Sphere> Spheres;

};

#endif