#include <algorithm>
#include <random>
#include <iostream>
#include <map>
#include "space.h"


void Space::input(std::istream* source)
{
   // first input size of the box
   *source >> this->axis_length[0] >> this->axis_length[1] >> this->axis_length[2];
   
   int sphere_id = 0;
   size_t num_objects = 0;  // number of particles of a certain component
   this->num_spheres = 0;

   *source >> num_objects;  // input number of particles of component 0
   
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

bool Space::sphere_in_vector(Sphere s1) {
   for(Sphere s: this->collided_spheres) {
      if(s.get_particle_id() == s1.get_particle_id()) {
         return true;
      }
   }
   return false;
}

long Space::count_collisions() {
   long num_collisions = 0;
   this->collided_spheres.clear();

   // iterate through unique pairs of components
   for(auto comp1 = this->components.begin(); comp1 != this->components.end(); comp1++)
      for(auto comp2 = comp1; comp2 != this->components.end(); comp2++) {
         
         // If sphere ID are equal, iterate through unique pairs of interactions within the component.
         if(comp1->second == comp2->second) {
            for(auto i = this->particles[comp1->second].begin(); std::next(i) != this->particles[comp1->second].end(); i++) {
               for(auto j = std::next(i); j != this->particles[comp2->second].end(); j++) {
                  // If theres a collision, increment number of collisions
                  if(i->check_collision(&(*j), this->axis_length)) num_collisions++;

                  // If collided_spheres is empty, or sphere not already in collided_spheres, add sphere to collided_sphere.
                  if(this->collided_spheres.empty() || !sphere_in_vector(*j)) this->collided_spheres.push_back(*j);
               }
            }
         }
         
         // Iterate through unique interactions between the two components
         else {
            for(auto i = this->particles[comp1->second].begin(); i != this->particles[comp1->second].end(); i++)
               for(auto j = this->particles[comp2->second].begin(); j != this->particles[comp2->second].end(); j++) {
                  // If theres a collision, increment number of collisions
                  if(i->check_collision(&(*j), this->axis_length)) num_collisions++;

                  // If the collided_spheres is empty, or sphere not already in collided_spheres, add sphere to collided_sphere.
                  if(this->collided_spheres.empty() || !sphere_in_vector(*j)) this->collided_spheres.push_back(*j);
            }
         }
      }
   
   return num_collisions;
}


/* 
int Space::mc_min_collision() {
   this->minimum_collisions=10;
   for (int i= 0; i<100000; i++) {
      int collisions = this->count_collisions();
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
      
      if(this->minimum_collisions > collisions) {this->minimum_collisions=collisions;}
   }
   return this->minimum_collisions;
}
*/


int Space::advance_mc_min_collision(){
   this->minimum_collisions=10;
   for (int i= 0; i<100000; i++) {
      srand(time(nullptr));
      int collisions = this->count_collisions();
      for(auto &kule : this->collided_spheres) {
         const float radius = kule.get_radius();
         float new_coords[3];
         new_coords[0] = radius + (rand() / ( RAND_MAX / ((this->axis_length[0]-radius)-radius) ) );
         new_coords[1] = radius + (rand() / ( RAND_MAX / ((this->axis_length[1]-radius)-radius) ) );
         new_coords[2] = radius + (rand() / ( RAND_MAX / ((this->axis_length[2]-radius)-radius) ) );
         kule.set_coordinates(new_coords);
      }; 
   if(this->minimum_collisions > collisions) this->minimum_collisions=collisions;
   }
   return this->minimum_collisions;
}

// Move all spheres within the defined bounds
void Space::move_spheres() {
   std::random_device dev;
   std::mt19937 gen(dev());

   // iterate through all components
   for(auto comp = this->components.begin(); comp != this->components.end(); comp++) {
      double radii = comp->first;
      // std::default_random_engine re;

      // Iterate through all spheres within a component
      for(auto &particle : this->particles[comp->second]) {
         float nu_coords[3];
         float collision_coords[3];

         for(int i = 0; i < 3; i++) {
            std::uniform_real_distribution<float> in_box(radii, this->axis_length[i] - radii);
            nu_coords[i] = in_box(gen);
         }
         particle.set_coordinates(nu_coords);
      } 

   }
}

void Space::move_marked() {
   std::random_device re;
   std::mt19937 generator(re());
   std::uniform_real_distribution<float> pct(0, 1);

   // iterate through spheres in collided_spheres
   for(auto &s: this->collided_spheres) {
      double radii = s.get_radius();
      float collision_coords[3]; 
      float nu_coords[3]; 
      s.get_coordinates(collision_coords);

      for(int i = 0; i < 3; i++) {
         float t = collision_coords[i] / this->axis_length[i];
         float p = pct(generator);

         std::uniform_real_distribution<float> forwards(collision_coords[i], this->axis_length[i] - collision_coords[i] - radii);
         std::uniform_real_distribution<float> backwards(radii, collision_coords[i] - radii);
         
         if(p > (1 - t)) nu_coords[i] = forwards(generator);
         else nu_coords[i] = backwards(generator);

      }
      s.set_coordinates(nu_coords);
   }
}



int Space::mc_min_collision() {
   this->minimum_collisions = 2;
   int temp_collisions = 0;
   
   // Initially place spheres in random positions the box as the configuration do not provide this.
   move_spheres();
   int collisions = this->count_collisions();
   if(collisions == 0) return collisions;
 
   for(int i = 0; i < 300000; i++) {
      move_marked();
      temp_collisions = collisions;
      collisions = this->count_collisions();

   }
   
   return collisions;
}


/*
int Space::mc_min_collision() {
   this->minimum_collisions = 10;
   int collisions = this->count_collisions();
   int i = 0;
   int old_collisions = 0;

   for(int i = 0; i < 1000000; i++) {
       move_marked(); 
       old_collisions = collisions;
       collisions = this->count_collisions();


      // when the number of collisions we've counted is less than the former minimum, set the minimum equal to the new count. 
      // But at the same time, what does the minimum do? It's useless...
       if(collisions < this->minimum_collisions) {this->minimum_collisions = collisions;}

       // After x iterations, and the number of collisions is equal to its previous iteration, terminate and return the collisions as we've converged to a "solution"
       if(collisions == old_collisions && (i > 500000)) {
         return collisions;
         std::cout << i;
       }

   }
   
   return collisions;
}
*/

