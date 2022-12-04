#ifndef SPHERE
#define SPHERE

#include <cmath>

class Sphere{
    public:
    Sphere(size_t i_pid, double rad ,double position[3]) { // Constructor. Gives each sphere an id, radius and coordinates.
      this->set_particle_id(i_pid);
      this->set_radius(rad);
      this->set_coordinates(position);
   }
        // get the different variables for the spheres
        double get_radius() const {return this->radius;}
        void get_coordinates(double* result);
        void get_new_coords(double* result);
        bool get_collision() const {return this->collisions;}

        // set the different variables to the spheres
        void set_radius(double r) {this->radius = r;}
        void set_particle_id(size_t i_pid) {this->particle_id = i_pid;}
        void set_coordinates(double* position) {
            this->new_coords[0] = position[0];
            this->new_coords[1] = position[1];
            this->new_coords[2] = position[2];
            this->update_coordinates();
        }
        
        void set_collision(bool collis){this->collisions=collis;} //set collision to true or false 
        
        int check_collision(Sphere* other_s, const double box_size[3]); //checks if to spheres is colliding
        int move_and_check_collision(Sphere* other_s, const double box_size[3]); //method to get fewer collisions
        
        
        void wall_collision(Sphere* other_s, const double box_size[3]); //checks if spheres are colliding with hard box in move_and_check_collisions
        void move_new_coords(double movement[3]) { //moves colliding spheres apart from each other
            this->new_coords[0] += movement[0];
            this->new_coords[1] += movement[1];
            this->new_coords[2] += movement[2];
        }
        
        void update_coordinates() {  //updates the coordinates after the spheres are moved
            this->coordinates[0]=this->new_coords[0];
            this->coordinates[1]=this->new_coords[1];
            this->coordinates[2]=this->new_coords[2];
        }
        
        void randomize_new_coords(const double box_size[3]); // randomize the sphere's coordinates within the box
        void print_coordinates(); // print out the current coordinates of the sphere.
         
    private:
        double coordinates[3] {0.0, 0.0, 0.0};
        double radius = 0.0;
        double new_coords[3] {0.0, 0.0, 0.0};
        size_t particle_id = 0;
        bool collisions = false;
        
};

#endif