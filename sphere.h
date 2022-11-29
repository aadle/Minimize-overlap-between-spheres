#ifndef SPHERE
#define SPHERE

#include <cmath>

class Sphere{
    public:
    Sphere(size_t i_pid, float rad ,float position[3]) {
      this->set_particle_id(i_pid);
      this->set_radius(rad);
      this->set_coordinates(position);
   }
        // get
        float get_radius() const {return this->radius;}
        void get_coordinates(float* result);
        void get_new_coords(float* result);
        bool get_collision() const {return this->collisions;}

        // set
        void set_radius(float r) {this->radius = r;}
        void set_particle_id(size_t i_pid) {this->particle_id = i_pid;}
        void set_coordinates(float* position) {
            this->new_coords[0] = position[0];
            this->new_coords[1] = position[1];
            this->new_coords[2] = position[2];
            this->update_coordinates();
        }

        void set_collision(bool collis){this->collisions=collis;}

        int check_collision(Sphere* other_s, const double box_size[3]);
        int move_and_check_collision(Sphere* other_s, const double box_size[3]);
        
        void wall_collision(Sphere* other_s, const double box_size[3]);
        void move_new_coords(float movement[3]){
            this->new_coords[0] += movement[0];
            this->new_coords[1] += movement[1];
            this->new_coords[2] += movement[2];
        }
        
        void update_coordinates(){
            this->coordinates[0]=this->new_coords[0];
            this->coordinates[1]=this->new_coords[1];
            this->coordinates[2]=this->new_coords[2];
        };
        void print_coordinates();

         
    private:
        float coordinates[3] {0.0, 0.0, 0.0};
        float radius = 0.0;
        float new_coords[3] {0.0, 0.0, 0.0};
        size_t particle_id = 0;
        bool collisions = false;
        
};

#endif