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

   int num_spheres = cube.get_num_spheres();
   std::cout << "Number of spheres: " <<num_spheres << '\n';

   long num_count = cube.count_collisions();
   std::cout << "Number of collisions: " << num_count << '\n';

   int i = 20000;

   std::cout << "Normal Monte Carlo simulation: " << cube.mc_min_collision(i)<< '\n';
   std::cout << "Advanced Monte Carlo simulation: "<< cube.advance_mc_min_collision(i) << '\n';
   std::cout << "Do Collision Minimum Collision Monte Carlo simulation: "<< cube.do_collision_min_collision(i) << '\n';

   auto end = std::chrono::steady_clock::now();
   std::cout << "Elapsed time in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " sec" << '\n';

   std::map<double, long> c = cube.get_comp();
   std::vector<std::vector<Sphere>> p = cube.get_particles();

   /*
   double coordi[3];
   for(auto comp = c.begin(); comp != c.end(); comp++)
      for(auto &m : p[comp->second]) {
         m.get_coordinates(coordi);
         std::cout << coordi[0] << '\t' << coordi[1] << '\t' << coordi[2] << '\t' << '\t' << m.get_radius() << '\n';
      }
   */
   

   return 0;
}