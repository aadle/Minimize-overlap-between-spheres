#ifndef SPACE
#define SPACE

#include <math.h>

class Space {
    public:
        // sets the volume of a unit cell
        void set_volume(float length) {this->volume = std::pow(length, 3);}

        // set number of unit cells. i.e. if 3, then we get a 3x3 box where a box has the volume of what is set above.  
        void set_unit_cells(const int num_cells);

    private:
        float volume = 0.0;

};

#endif