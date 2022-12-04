#include "sphere.h"
#include <iostream>
#include <omp.h>

int Sphere::check_collision(Sphere* other_s, const double box_size[3]) {
   int tid = omp_get_thread_num();
   //cheks if this sphere is colliding with an other sphere(other_s) by using pythagoras
   double sq_distance = 0.0;
   
   for (int i=0; i<3; i++){  
      // 1-dimensional distance
      double distance = other_s->coordinates[i] - this->coordinates[i];

      sq_distance += distance*distance;
   }
   double sum_radius = (this->radius + other_s->radius);
   //if the distance between thw spheres are larger then the sum of the radius, they are overlapping.
   bool collision = (sq_distance < sum_radius*sum_radius);

   if(sq_distance < 0.25*sum_radius*sum_radius) collision = 8;  // extra punishment for big overlap
   else if(sq_distance < sum_radius*sum_radius) collision = 1;

   if(collision) {
      // set both sphere.collisons to true if they collide
      this->collisions = true;
      other_s->set_collision(true);
   }
   
   return collision; 
}

void Sphere::get_coordinates(double* result) {
   int tid = omp_get_thread_num();
   // reads the coordinates into the array
   this->coordinates;
   for(int i = 0; i < 3; i++) {
      result[i] = coordinates[i];
   }
}

void Sphere::get_new_coords(double* result) {
   int tid = omp_get_thread_num();
   // reads the new_coords into the array
   this->new_coords;
   for(int i = 0; i < 3; i++) {
      result[i] = new_coords[i];
   }
}

int Sphere::move_and_check_collision(Sphere* other_s, const double box_size[3]) {
   /*cheks if this sphere is colliding with another sphere(other_s) by using pythagoras
    and move the new_coords so they do not collide*/
   double sq_distance = 0.0;

   for (int i=0; i<3; i++){  
      // 1-dimensional distance
      double distance = other_s->coordinates[i] - this->coordinates[i];

      sq_distance += distance*distance;
   }
   double sum_radius = (this->radius + other_s->radius);
   //if the distance between thw spheres are larger then the sum of the radius, they are overlapping.
   bool collision = (sq_distance < sum_radius*sum_radius);

   if(sq_distance < 0.25*sum_radius*sum_radius) collision = 8;     // extra punishment for big overlap
   else if(sq_distance < sum_radius*sum_radius) collision = 1;

   if(collision) {
      this->collisions = true;
      other_s->set_collision(true);
      if (sq_distance!=0){
         double s1_collide_amount[3];
         double s2_collide_amount[3];
         double collision_coeff = ((sum_radius/(sqrt(sq_distance)))-1)/2; // half of what the distance must increase

         for (int i=0; i<3; i++){ 
            // calculating how mush the spheres must move
            s1_collide_amount[i]= (this->coordinates[i]-other_s->coordinates[i])*collision_coeff;
            s2_collide_amount[i]= -s1_collide_amount[i];
         }
         
         // move the new coords
         this->move_new_coords(s1_collide_amount);
         other_s->move_new_coords(s2_collide_amount);
         this->wall_collision(other_s, box_size); //moves both spheres so they do not collide with each other or the wall
      }
      else{
         std::cout<<"h";
         this->randomize_new_coords(box_size);
      }
   }   
   return collision;
}

void Sphere::wall_collision(Sphere* other_s, const double box_size[3]){
   // moves both sphere the amount they collide with the walls
   double collision_amount[3] = {0, 0, 0};
   double coords1[3];
   this->get_new_coords(coords1);
   double coords2[3];
   other_s->get_new_coords(coords2);

   const double* s_coords[2] = {coords1, coords2};
   double s_radius[2] = {this->get_radius(), other_s->get_radius()};
   for (int i=0; i<3; i++){
      for (int j=0; j<2; j++){
         if (s_coords[j][i]-s_radius[j] < 0) {collision_amount[i]+= s_radius[j]-s_coords[j][i];}
         if (s_coords[j][i]+s_radius[j] > box_size[i]) {collision_amount[i] += box_size[i]-s_radius[j]-s_coords[j][i];}
      }
   }
   
   // move the new coords
   this->move_new_coords(collision_amount);
   other_s->move_new_coords(collision_amount);
}

void Sphere::print_coordinates(){
   // print the coordinates to the sphere
   for(int i=0; i<3; i++){
      std::cout<<this->coordinates[i]<<"\t";
   }
   std::cout<<"\n";
}


void Sphere::randomize_new_coords(const double box_size[3]){
   double radius = this->radius;
   this->new_coords[0] = radius + (rand() / ( RAND_MAX / ((box_size[0] - radius) - radius) ) );
   this->new_coords[1] = radius + (rand() / ( RAND_MAX / ((box_size[1] - radius) - radius) ) );
   this->new_coords[2] = radius + (rand() / ( RAND_MAX / ((box_size[2] - radius) - radius) ) );
}

