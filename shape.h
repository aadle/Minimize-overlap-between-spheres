#ifndef SHAPE
#define SHAPE

// #include <vector>

class Shape {
    public:
        // get
        const float* get_position() const {return this->coordinates;} // return as const as we don't want the positional coordinates we return out to be able to change
        float get_volume(); // General volume method which we can overload for different shapes.

        // set 
        void set_coordinates(float* position) {
            for(int i=0; i < sizeof(position); i++) {this->coordinates[i] = position[i];}
        } // perhaps not very general and doesn't look pretty with the for-loop but it works.

    private:
        float coordinates[3] {0.0, 0.0, 0.0};
        // std::vector<float> coordinates{0.0, 0.0, 0.0}; Don't use vector, use an array as the size doesn't vary. It's always 3 in size (x, y, z)
};

#endif