#include <cassert>
#include <fstream>
#include <iostream>
#include <chrono>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   std::srand(time(nullptr)); // randomizes a seed for the simulation
   assert(argc > 1); 
   auto start = std::chrono::steady_clock::now(); // start timer
   
   Space cube;
   std::ifstream input_file{argv[1]};
   std::istream& inputs = input_file;
   cube.input(&inputs);
   input_file.close();

   cube.randomize_all_coordinates();

   std::cout << "Number of spheres:\t" << cube.get_num_spheres() << '\n';

   std::cout << "Number of collisions:\t" << cube.count_collisions() << '\n' << '\n';

   int num_iterations = 20000; // number of iterations

   std::cout << "Normal Monte Carlo simulation:\t" << cube.mc_min_collision(num_iterations) << '\n';
   std::cout << "Advanced Monte Carlo simulation:\t"<< cube.advance_mc_min_collision(num_iterations) << '\n';
   std::cout << "Do Collision simulation:\t"<< cube.do_collision_min_collision(num_iterations) << '\n' << '\n';

   auto end = std::chrono::steady_clock::now(); // timer stop
   // debug output for time elapsed
   std::cout << "Runtime in seconds: "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << " sec" << '\n' << '\n';

   /*
   Debugging output of all the spheres and its coordinates in the box.

   std::map<double, long> c = cube.get_comp();
   std::vector<std::vector<Sphere>> p = cube.get_particles();

   double coordi[3];
   for(auto comp = c.begin(); comp != c.end(); comp++)
      for(auto &m : p[comp->second]) {
         m.get_coordinates(coordi);
         std::cout << coordi[0] << '\t' << coordi[1] << '\t' << coordi[2] << '\t' << '\t' << m.get_radius() << '\n';
      }
   */

   return 0;
}