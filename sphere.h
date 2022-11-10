#ifndef SPHERE
#define SPHERE

#include <cmath>

class Sphere{
    public:
        // get
        float get_radius() const {return this->radius;}
        const float* get_coordinates() const {return this->coordinates;}

        // set
        void set_radius(float r) {this->radius = r;}
        void set_particle_id(size_t i_pid) {this->particle_id = i_pid;}
        void set_coordinates(float* position) {
            this->coordinates[0] = position[0];
            this->coordinates[1] = position[1];
            this->coordinates[2] = position[2];
        }
         
    private:
        float coordinates[3] {0.0, 0.0, 0.0};
        float radius = 0.0;
        size_t particle_id = 0;
        
};

#endif