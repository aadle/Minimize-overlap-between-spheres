#include <cassert>
#include <fstream>
#include <iostream>
#include <chrono>
#include <omp.h>

#include "space.h"
#include "sphere.h"

int main(int argc, char** argv)
{
    srand(time(nullptr));
    assert(argc > 1);
    //auto start = std::chrono::steady_clock::now();
    Space cube;
    std::ifstream input_file{argv[1]};
    std::istream& inputs =input_file;
    cube.input(&inputs);
    input_file.close();

    int Num_parallel = 6;
    Space cubes[Num_parallel];
    for (int i=0; i<Num_parallel; i++ ){
        cubes[i] = cube;
    }

    long coll[Num_parallel]; 
    
    #pragma omp parallel num_threads(Num_parallel)
    { 
    #pragma omp for
    for (int i=0; i<Num_parallel; i++){

        srand(i+time(NULL));
        coll[i] = cubes[i].do_collision_min_collision();
        std::cout<<"\n"<<coll[i]<<"\n";
    }
    }
    for (Space s:cubes){
        std::cout<<"\n"<<s.get_minimum_collisions()<<"\n";
    }
    
}
