#include <iostream>
#include "space.h"

/*
 * Preface:
 * Majority of the code in Space::input and Space::count_collisions is based off of Martin Horch's code file "box.cpp" which can be found here:
 * https://home.bawue.de/~horsch/teaching/inf205/src/pbc-mic.zip
 * The code files are released under the conditions of the CC BY-NC-SA 4.0 License. 
 * 
 * It has been modified to accomodate the rest of our code.
 */

void Space::input(std::istream* source)
{
   // first input size of the box
   *source >> this->axis_length[0] >> this->axis_length[1] >> this->axis_length[2];
   
   long sphere_id = 0;
   size_t num_objects = 0;  // number of particles of a certain component

   *source >> num_objects;  // input number of particles of component 0

   while(num_objects != 0)
   {
      // create new component
      double sphere_radius = 0.0;
      *source >> sphere_radius;
      
      sphere_radius = sphere_radius/2;

      // inserts sphere with unique sphere id
      this->components.insert({sphere_radius, sphere_id});

      this->particles.push_back(std::vector<Sphere>());

      // read all the particles
      for(size_t i = 0; i < num_objects; i++)
      {
         // read the coordinates for the spheres
        double coords[3];
        *source >> coords[0] >> coords[1] >> coords[2];
        
        this->particles[sphere_id].push_back(Sphere(this->num_spheres++, sphere_radius, coords));
        }
        // updates sphere_id
        sphere_id++;
     *source >> num_objects;
    }
}

// Sets axis lengths for the cuboid space
void Space::set_axis_length(double length[3]) {
    this->axis_length[0] = length[0];
    this->axis_length[1] = length[1];
    this->axis_length[2] = length[2];
}

// Counts number of collisions occuring in the space
long Space::count_collisions() {

   // Initialize the spheres' collision variable.
   for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            kule.set_collision(false);
         }
   }

   long num_collisions = 0; 

   // Iterate through unique pairs of components
   for(auto comp1 = this->components.begin(); comp1 != this->components.end(); comp1++)
      for(auto comp2 = comp1; comp2 != this->components.end(); comp2++) {
         
         // If components are equal, iterate through unique pairs of particles within the component.
         if(comp1->second == comp2->second) {
            for(auto i = this->particles[comp1->second].begin(); std::next(i) != this->particles[comp1->second].end(); i++){
               for(auto j = std::next(i); j != this->particles[comp2->second].end(); j++) {
                  
                  // If sphere is colliding, increment number of collisions in the space accordingly
                  num_collisions += i->move_and_check_collision(&(*j), this->axis_length);
               }
            }
         }
         
         // Else, iterate through unique pairs of particles between two components.
         else {
            for(auto i = this->particles[comp1->second].begin(); i != this->particles[comp1->second].end(); i++)
               for(auto j = this->particles[comp2->second].begin(); j != this->particles[comp2->second].end(); j++) {

                  // If sphere is colliding, increment number of collisions in the space accordingly
                  num_collisions += i->move_and_check_collision(&(*j), this->axis_length);
            }
         }
      }
   
   return num_collisions;
}

// General Monte Carlo simulation moving all spheres in the space.
long Space::mc_min_collision(int num_iterations) {
   // this->randomize_all_coordinates();
   this->minimum_collisions = count_collisions();
   for (long i = 0; i < num_iterations; i++) {
      for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            const double radius = kule.get_radius();
            double new_coords[3];

            // Generate new coordinates within the bounds of the box
            new_coords[0] = radius + (rand() / ( RAND_MAX / ((this->axis_length[0]-radius)-radius) ) );
            new_coords[1] = radius + (rand() / ( RAND_MAX / ((this->axis_length[1]-radius)-radius) ) );
            new_coords[2] = radius + (rand() / ( RAND_MAX / ((this->axis_length[2]-radius)-radius) ) );
            kule.set_coordinates(new_coords);
         }
      }
      long collisions = this->count_collisions();
      if(this->minimum_collisions > collisions) {this->minimum_collisions=collisions;}
   }
   return this->minimum_collisions;
}

// Monte Carlo simulation only moving colliding spheres in the space.
long Space::advance_mc_min_collision(int num_iterations) {
   // this->randomize_all_coordinates();
   this->minimum_collisions = count_collisions();
   for (long i = 0; i < num_iterations; i++) {
      for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            if (kule.get_collision()) {
               const double radius = kule.get_radius();
               double new_coords[3];

               // Generate new coordinates within the bounds of the box
               new_coords[0] = radius + (rand() / ( RAND_MAX / ((this->axis_length[0] - radius) - radius) ) );
               new_coords[1] = radius + (rand() / ( RAND_MAX / ((this->axis_length[1] - radius) - radius) ) );
               new_coords[2] = radius + (rand() / ( RAND_MAX / ((this->axis_length[2] - radius) - radius) ) );
               kule.set_coordinates(new_coords);
            }
         }
      }
      long collisions = this->count_collisions();
      if(this->minimum_collisions > collisions) {this->minimum_collisions=collisions;}
   }
   return this->minimum_collisions;
}

// Randomize the coordinates of each sphere within the box
void Space::randomize_all_coordinates() {
   for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            const double radius = kule.get_radius();
            double new_coords[3];
            new_coords[0] = radius + (rand() / ( RAND_MAX / ((this->axis_length[0]-radius)-radius) ) );
            new_coords[1] = radius + (rand() / ( RAND_MAX / ((this->axis_length[1]-radius)-radius) ) );
            new_coords[2] = radius + (rand() / ( RAND_MAX / ((this->axis_length[2]-radius)-radius) ) );
            kule.set_coordinates(new_coords);
         }; 
   }
   
}

// Non Monte Carlo solution to minimize the collisions
long Space::do_collision_min_collision(int num_iterations) {
   // this->randomize_all_coordinates();
   this->minimum_collisions = count_collisions();
   for (long i = 0; i < num_iterations; i++) {
      for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            if (kule.get_collision()) {
               kule.update_coordinates();
            }
         }
      }
      long collisions = this->count_collisions();
      if(this->minimum_collisions > collisions) {this->minimum_collisions = collisions;}
      if (collisions == 0) {
         std::cout <<"got 0 collisions after" << i << "craches\n";
         return 0;
      }
   }
   return this->minimum_collisions;
}
