#include "sphere.h"
#include <iostream>


int main() {
    Sphere circle;
    const float* sphere_coord = circle.get_position();
    std::cout << sphere_coord[0] << "\t" << sphere_coord[1] << "\t" << sphere_coord[2] << "\n";
    float new_coordinates1[3] {123, 351, 10.6};
    circle.set_coordinates(new_coordinates1);
    circle.set_radius(1.616);
    float rad = circle.get_radius();
    float dia = circle.get_diameter();
    float vol = circle.get_volume();
    std::cout << rad << "\t" << dia << "\t";
}