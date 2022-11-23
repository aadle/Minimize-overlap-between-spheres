#include <iostream>
#include "space.h"


void Space::input(std::istream* source)
{
   // first input size of the box
   *source >> this->axis_length[0] >> this->axis_length[1] >> this->axis_length[2];
   
   int sphere_id = 0;
   size_t num_objects = 0;  // number of particles of a certain component

   *source >> num_objects;  // input number of particles of component 0
   // this->num_spheres=num_spheres+num_objects;
   while(num_objects != 0)
   {
      // create new component
      float sphere_radius = 0.0;
      *source >> sphere_radius;
      sphere_radius = sphere_radius/2; // change: input is diameter, instantly get radii after reading input

      // inserts sphere with unique sphere id
      this->components.insert({sphere_radius, sphere_id});

      // insert a new vector
      this->particles.push_back(std::vector<Sphere>());

      // now read all the particles
      for(size_t i = 0; i < num_objects; i++)
      {
         // read the coordinates for the spheres
        float coords[3];
        *source >> coords[0] >> coords[1] >> coords[2];

         // Apply periodic boundary conditions
         for(int k = 0; k < 3; k++) {
            while(coords[k] < 0.0) coords[k] += this->axis_length[k];
            while(coords[k] > this->axis_length[k]) coords[k] -= this->axis_length[k];
         }
        
        this->particles[sphere_id].push_back(Sphere(this->num_spheres++, sphere_radius, coords));
        }
        // updates sphere_id
        sphere_id++;
     *source >> num_objects;
    }
}

void Space::set_axis_length(float length[3]) {
    this->axis_length[0] = length[0];
    this->axis_length[1] = length[1];
    this->axis_length[2] = length[2];
}

long Space::count_collisions() {
   long num_collisions = 0;

   // iterate through unique pairs of components
   for(auto comp1 = this->components.begin(); comp1 != this->components.end(); comp1++)
      for(auto comp2 = comp1; comp2 != this->components.end(); comp2++) {
         
         // If components are equal, iterate through unique pairs of particles within the component.
         if(comp1->second == comp2->second) {
            for(auto i = this->particles[comp1->second].begin(); std::next(i) != this->particles[comp1->second].end(); i++){
               for(auto j = std::next(i); j != this->particles[comp2->second].end(); j++) {
                  
                  if(i->check_collision(&(*j), this->axis_length)) {
                     num_collisions++;
                     this->collided_spheres.push_back(*j);
                  }
               }
            }
         }
         
         else {
            for(auto i = this->particles[comp1->second].begin(); i != this->particles[comp1->second].end(); i++)
               for(auto j = this->particles[comp2->second].begin(); j != this->particles[comp2->second].end(); j++) {
                  if(i->check_collision(&(*j), this->axis_length)) {
                     num_collisions++;
                     this->collided_spheres.push_back(*j);
                  }
            }
         }
      }
   
   return num_collisions;
}


int Space::calculate_min_collision() {
   this->minimum_collisions=10;
   for (int i= 0; i<100000; i++) {
      for(std::vector<Sphere> &sphere_vector : this->particles) {
         for(Sphere &kule : sphere_vector) {
            const float radius = kule.get_radius();
            float new_coords[3];
            new_coords[0] = radius + (rand() / ( RAND_MAX / ((this->axis_length[0]-radius)-radius) ) );
            new_coords[1] = radius + (rand() / ( RAND_MAX / ((this->axis_length[1]-radius)-radius) ) );
            new_coords[2] = radius + (rand() / ( RAND_MAX / ((this->axis_length[2]-radius)-radius) ) );
            kule.set_coordinates(new_coords);
         }; 
      }
      int collisions = this->count_collisions();
      if(this->minimum_collisions > collisions) {this->minimum_collisions=collisions;}
   }
   return this->minimum_collisions;
}
