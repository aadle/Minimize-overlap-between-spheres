#include "sphere.h"
#include <iostream>

int Sphere::check_collision(Sphere* other_s, const double box_size[3]) {
   float sq_distance = 0.0;

   for (int i=0; i<3; i++){  
      // 1-dimensional distance
      float distance = other_s->coordinates[i] - this->coordinates[i];

      sq_distance += distance*distance;
   }
   float sum_radius = (this->radius + other_s->radius);
   bool collision = (sq_distance < sum_radius*sum_radius);

   if(sq_distance < 0.25*sum_radius*sum_radius) collision = 8;  
   else if(sq_distance < sum_radius*sum_radius) collision = 1;

   if(collision) this->collisions = true;
   else this->collisions = false;   
   
   return collision;
}