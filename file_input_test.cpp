#include <cassert>
#include <fstream>
#include <iostream>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   assert(argc > 1);
   
   Space cube;
   std::ifstream input_file{argv[1]};
   std::istream& inputs =input_file;
   cube.input(&inputs);
   input_file.close();


   std::vector<Sphere> Sphere_list = cube.get_spheres();
   for(Sphere s:Sphere_list){
   const float* sphere_coord = s.get_coordinates();
   std::cout << sphere_coord[0] << "\t" << sphere_coord[1] << "\t" << sphere_coord[2] << "\n";
   }
}