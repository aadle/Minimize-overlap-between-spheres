#ifndef SHAPE
#define SHAPE

// #include <vector>

class Shape {
    public:
        // get
        const float* get_coordinates() const {return this->coordinates;} // return as const as we don't want the positional coordinates we return out to be able to change
        float get_volume(); // General volume method which we can overload for different shapes.

        // set 
        void set_coordinates(float* position) {
            this->coordinates[0] = position[0];
            this->coordinates[1] = position[1];
            this->coordinates[2] = position[2];
        }

    private:
        float coordinates[3] {0.0, 0.0, 0.0};
        // std::vector<float> coordinates{0.0, 0.0, 0.0}; Don't use vector, use an array as the size doesn't vary. It's always 3 in size (x, y, z)
};

#endif