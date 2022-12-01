#include <cassert>
#include <fstream>
#include <iostream>
#include <chrono>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   srand(time(nullptr));
   #pragma omp parallel
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

   std::cout << cube.mc_min_collision()<< '\n' << cube.advance_mc_min_collision() << '\n';

   auto end = std::chrono::steady_clock::now();
   std::cout << "Elapsed time in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " sec" << '\n';

   std::map<double, int> c = cube.get_components();
   std::vector<std::vector<Sphere>> p = cube.get_particles();

   double coordi[3];
   for(auto comp = c.begin(); comp != c.end(); comp++)
      for(auto &m : p[comp->second]) {
         m.get_coordinates(coordi);
         std::cout << coordi[0] << '\t' << coordi[1] << '\t' << coordi[2] << '\t' << '\t' << m.get_radius() << '\n';
      }

   return 0;
}