#include <cassert>
#include <fstream>
#include <iostream>
#include <time.h>
#include <chrono>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   assert(argc > 1);

   auto start = std::chrono::steady_clock::now();
   Space cube;
   std::ifstream input_file{argv[1]};
   std::istream& inputs =input_file;
   cube.input(&inputs);
   input_file.close();

   long num_count = cube.count_collisions();
   std::cout << num_count << '\n';

   std::vector<Sphere> coll = cube.get_spheres();
   std::cout << coll.size() << '\n';

   std::vector<Sphere> Sphere_list = cube.get_spheres();
   
   std::cout << "Monte Carlo Minimum Collision: " << cube.mc_min_collision() << '\n';

   float coordi[3];

   for(auto &s: cube.get_spheres()) {
      s.get_coordinates(coordi);
      float q = s.get_radius();
      std::cout << coordi[0] << "\t" << coordi[1] << "\t" << coordi[2] << "\t" << "\t" << q << '\n';
   }
   auto end = std::chrono::steady_clock::now();
   std::cout << "Elapsed time in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " sec" << '\n';
   
   return 0;


   /*
   std::cout << "Advanced Monte Carlo Minimum Collision: " << cube.advance_mc_min_collision() << '\n';  

   for(auto &s: cube.get_spheres()) {
      s.get_coordinates(coordi);
      std::cout << coordi[0] << "\t" << coordi[1] << "\t" << coordi[2] << '\n';
   }
   */
}