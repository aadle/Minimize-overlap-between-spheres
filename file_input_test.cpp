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
   
   std::cout << cube.mc_min_collision()<<'\t'<< cube.advance_mc_min_collision();
}