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
        std::vector<Sphere> get_spheres() {return this->spheres;}

        long count_collisions();

    private:
        int num_spheres = 0;  // total number of spheres
        float volume = 0.0;
        double axis_length[3];
        std::vector<Sphere> spheres;
        std::multimap<double, int, std::greater<int>> components;
        std::vector<std::vector<Sphere>> particles;

};

#endif