
#include <algorithm>
#include <random>
#include <iostream>


int main() {
    std::random_device re;
    std::mt19937 generator(re());

    for(int i = 0; i < 10; i++) {;
        std::uniform_real_distribution<float> unif(0, 1);
        float a_random_double = unif(re);

        std::cout << a_random_double << '\n';
    }
}
