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

        const long get_minimum_collisions() {return this->minimum_collisions;} // get the minimum number of collisions in the box
        std::map<double, long> get_comp() const {return this->components;}
        std::vector<std::vector<Sphere>> get_particles() {return this->particles;}

        long count_collisions(); // counts the number of collisions
        long do_collision_min_collision(int num_iterations); // non-Monte Carlo solution
        long mc_min_collision(int num_iterations); // Random Monte Carlo Solution
        long advance_mc_min_collision(int num_iterations); // Only move colliding spheres Monte Carlo solution
        
        void randomize_all_coordinates(); // randomize the coordinates
        long get_num_spheres() {return this->num_spheres;} // get the number of spheres in the box


    private:
        long num_spheres = 0;  // total number of spheres
        double volume = 0.0; // volume of the box
        double axis_length[3]; // axis lengths of the box in the 3 directions
        long minimum_collisions = 0; // minimum collisions 
        std::map<double, long> components; // map containing the unique sphere radii.
        std::vector<std::vector<Sphere>> particles; // Vector of vectors containing Spheres. The collection of all spheres in the box.

};

#endif