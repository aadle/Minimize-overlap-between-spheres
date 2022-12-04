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
        void set_axis_length(double length[3]);

        int get_N() const {return this->num_spheres;}
        const long get_minimum_collisions() {return this->minimum_collisions;}
        const double* get_coordinates() const {return this->axis_length;} // useless?
        std::map<double, int> get_comp() const {return this->components;}
        std::vector<Sphere> get_spheres() {return this->collided_spheres;}

        std::map<double, int> get_components() {return this->components;}
        std::vector<std::vector<Sphere>> get_particles() {return this->particles;}

        long count_collisions();

        long move_and_count_collisions();
        int mc_min_collision();

        int advance_mc_min_collision();

        long do_collision_min_collision();
        void randomize_all_coordinates();
        void print_coordinates();


    private:
        int num_spheres = 0;  // total number of spheres
        double volume = 0.0;
        double axis_length[3];
        long minimum_collisions = 0;
        std::vector<Sphere> collided_spheres;
        std::map<double, int> components;
        std::vector<std::vector<Sphere>> particles;

};

#endif