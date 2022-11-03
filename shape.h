#ifndef SHAPE
#define SHAPE

// #include <vector>

class Shape {
    public:
        // get
        float* get_position() const {return this->coordinates;}

        // set
        void set_coordinates(float* position[3]) {this->coordinates;}

    private:
        float coordinates[3] = {0.0, 0.0, 0.0};
        // std::vector<float> coordinates{0.0, 0.0, 0.0}; Don't use vector, use an array as the size doesn't vary. It's always 3 in size (x, y, z)
};

#endif