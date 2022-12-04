#include <cassert>
#include <fstream>
#include <iostream>
#include <chrono>
#include <omp.h>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   //std::srand(time(nullptr)); // randomizes a seed for the simulation
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

   int num_iterations = 10000; // number of iterations

   int Num_parallel = 6;
   Space cubes[Num_parallel];
   for (int i=0; i<Num_parallel; i++ ){
        cubes[i] = cube;
    }

    long do_coll[Num_parallel];
    long mc_coll[Num_parallel];
    long adv_mc_coll[Num_parallel];   
    
    #pragma omp parallel num_threads(Num_parallel)
    { 
    #pragma omp for
    for (int i=0; i<Num_parallel; i++){

        srand(i+time(NULL));
        cubes[i].randomize_all_coordinates();
        do_coll[i] = cubes[i].do_collision_min_collision(num_iterations);
        mc_coll[i] = cubes[i].mc_min_collision(num_iterations);
        adv_mc_coll[i] = cubes[i].advance_mc_min_collision(num_iterations);
    }
    }
    int do_min = do_coll[0];
    int mc_min = mc_coll[0];
    int adv_mc_min = adv_mc_coll[0];
    for (int i=1; i<Num_parallel; i++){
         std::cout<<do_coll[i];
         if(do_min > do_coll[i]){ do_min = do_coll[i];}
         if(mc_min > mc_coll[i]){ mc_min = mc_coll[i];}
         if(adv_mc_min > adv_mc_coll[i]){ adv_mc_min = adv_mc_coll[i];}
    }

   std::cout << "Normal Monte Carlo simulation:\t" << mc_min<< '\n' ;// cube.mc_min_collision(num_iterations) << '\n';
   std::cout << "Advanced Monte Carlo simulation:\t"<<adv_mc_min<< '\n' ;// cube.advance_mc_min_collision(num_iterations) << '\n';
   std::cout << "Do Collision simulation:\t"<< do_min<< '\n' ;//cube.do_collision_min_collision(num_iterations) << '\n' << '\n';

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