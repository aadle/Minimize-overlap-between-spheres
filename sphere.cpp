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
   
   return collision;
}

void Sphere::get_coordinates(float* result) {
   this->coordinates;
   for(int i = 0; i < 3; i++) {
      result[i] = coordinates[i];
   }
}

void Sphere::get_new_coords(float* result) {
   this->new_coords;
   for(int i = 0; i < 3; i++) {
      result[i] = new_coords[i];
   }
}

int Sphere::move_and_check_collision(Sphere* other_s, const double box_size[3]) {
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

   if(collision) {
      this->collisions = true;
      other_s->set_collision(true);
      float s1_collide_amount[3];
      float s2_collide_amount[3];
      float collision_coeff = ((sum_radius/(sqrt(sq_distance)))-1)/2;

      for (int i=0; i<3; i++){ 
         s1_collide_amount[i]= (this->coordinates[i]-other_s->coordinates[i])*collision_coeff;
         s2_collide_amount[i]= -s1_collide_amount[i];
      }
      
      this->move_new_coords(s1_collide_amount);
      other_s->move_new_coords(s2_collide_amount);
      this->wall_collision(other_s, box_size);
      
   }   
   return collision;
}

void Sphere::wall_collision(Sphere* other_s, const double box_size[3]){
   float collision_amount[3] = {0, 0, 0};
   float coords1[3];
   this->get_new_coords(coords1);
   float coords2[3];
   other_s->get_new_coords(coords2);
   const float* s_coords[2] = {coords1, coords2};
   float s_radius[2] = {this->get_radius(), other_s->get_radius()};
   for (int i=0; i<3; i++){
      for (int j=0; j<2; j++){
         if (s_coords[j][i]-s_radius[j] < 0) {collision_amount[i]+= s_radius[j]-s_coords[j][i];}
         if (s_coords[j][i]+s_radius[j] > box_size[i]) {collision_amount[i] += box_size[i]-s_radius[j]-s_coords[j][i];}
      }
   }
   
   this->move_new_coords(collision_amount);
   other_s->move_new_coords(collision_amount);
}

void Sphere::print_coordinates(){
   for(int i=0; i<3; i++){
      std::cout<<this->coordinates[i]<<"\t";
   }
   std::cout<<"\n";
}

