#include "sphere.h"

int Sphere::check_collision(Sphere* other_s){
   float sq_distance = 0.0;

   for (int i=0; i<3; i++){
        
        // 1-dimensional distance
        float distance = this->coordinates[i] - other_s->coordinates[i];

        sq_distance += distance*distance;
   }
   float sum_radius = this->radius + other_s->radius;
   int collision = 0;
   if(sq_distance < 0.25*sum_radius*sum_radius) collision = 8;  
   else if(sq_distance < sum_radius*sum_radius) collision = 1;

   return collision;
}