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
        void set_axis_length(double length[3]); // sets the volume of a unit cell

        const long get_minimum_collisions() {return this->minimum_collisions;}
        std::map<double, long> get_comp() const {return this->components;}
        std::vector<std::vector<Sphere>> get_particles() {return this->particles;}

        long count_collisions();
        long do_collision_min_collision(int num_iterations);
        long mc_min_collision(int num_iterations);
        long advance_mc_min_collision(int num_iterations);
        
        void randomize_all_coordinates();
        void prlong_coordinates();
        long get_num_spheres() {return this->num_spheres;}


    private:
        long num_spheres = 0;  // total number of spheres
        double volume = 0.0;
        double axis_length[3];
        long minimum_collisions = 0;
        std::map<double, long> components;
        std::vector<std::vector<Sphere>> particles;

};

#endif