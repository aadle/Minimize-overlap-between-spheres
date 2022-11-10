#include "space.h"

void Space::set_axis_length(float length[3]) {
    /*
    for(int i=0; i < 3; i++) {
    this->axis_length[i] = length[i];
    }
    */
    this->axis_length[0] = length[0];
    this->axis_length[1] = length[1];
    this->axis_length[2] = length[2];
}