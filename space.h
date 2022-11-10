#ifndef SPACE
#define SPACE

#include <math.h>

class Space {
    public:
        // sets the volume of a unit cell
        void set_axis_length(float length[3]);

        long count_collisions();

    private:
        float volume = 0.0;
        double axis_length[3];

};

#endif