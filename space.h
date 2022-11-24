#ifndef SPACE
#define SPACE

#include <math.h>
#include <vector>
#include <iostream>
#include <map>

#include "sphere.h"

class Space {
    public:
        void input(std::istream* source);  // read from *source
        // sets the volume of a unit cell
        void set_axis_length(float length[3]);

        int get_N() const {return this->num_spheres;}
        const double* get_coordinates() const {return this->axis_length;} // useless?
        std::map<double, int> get_comp() const {return this->components;}
        std::vector<Sphere> get_spheres() {return this->collided_spheres;}

        long count_collisions();

        int mc_min_collision();

        int advance_mc_min_collision();

    private:
        int num_spheres = 0;  // total number of spheres
        float volume = 0.0;
        double axis_length[3];
        int minimum_collisions = 0;
        std::vector<Sphere> collided_spheres;
        std::map<double, int> components;
        std::vector<std::vector<Sphere>> particles;

};

#endif