#include <cstdlib>
#include <SDL2/SDL.h>
#include <cmath>

#include <iostream>

class Perlin{
public:
    uint16_t MAP_WIDTH;
    uint16_t MAP_HEIGHT;
    uint8_t frequency; // determines the size of each "chunk", chunks are still 16x16
    unsigned int seed;
    uint16_t HEIGHT_MAP_MAX = 255; // 0 x 1111 1111, determines the max elivation of the map 

    uint8_t* noisemap;

    Perlin(const uint16_t MAP_WIDTH, const uint16_t MAP_HEIGHT, uint8_t* noisemap, const uint8_t frequency, const unsigned int seed)
    : MAP_WIDTH(MAP_WIDTH-(MAP_WIDTH%frequency)), MAP_HEIGHT(MAP_HEIGHT-(MAP_HEIGHT%frequency)), noisemap(noisemap), frequency(frequency), seed(seed){
        for(int i=0;i<(MAP_HEIGHT/frequency)-1;i++){
            for(int j=0;j<(MAP_WIDTH/frequency)-1;j++){
                fillChunk(j*(frequency-1), i*(frequency-1), (j+1)*(frequency-1), (i+1)*(frequency-1));
            }
        }
    }
    ~Perlin(){}
private:
    struct vector2{
        float x, y;
        vector2(float x, float y) : x(x),y(y){}
        float dot(float x1, float y1){ return x*x1+y*y1; }
    };

    vector2 randomgradient(unsigned int val){
        // XorShift algorithm for random numbers
        unsigned int random = seed+val;
        random ^= (random<<13);
        random ^= (random>>14);
        random ^= (random<<8);
        uint8_t amplitude = 2;

        return vector2(std::cos(random>>2), std::sin(random<<1)); // shift is arbituary but reduces overlap
    }

    float smoothStep(float a, float b, float normalized_step){ // returns a value between a inclusive and b inclusive
        return a + (b-a) * (3 - 2*normalized_step)*normalized_step*normalized_step;
    }

    void fillChunk(int x1, int y1, int x2, int y2){
        // gets the corners of the map
        vector2 gradient_top_left     = randomgradient(x1+y1*MAP_WIDTH);
        vector2 gradient_top_right    = randomgradient(x2+y1*MAP_WIDTH);
        vector2 gradient_bottom_left  = randomgradient(x1+y2*MAP_WIDTH);
        vector2 gradient_bottom_right = randomgradient(x2+y2*MAP_WIDTH);

        for(uint8_t i=0;i<frequency;i++){
            for(uint8_t j=0;j<frequency;j++){
                float normalized_i     = static_cast<float>(i)/(frequency-1); // ciels m
                float normalized_j     = static_cast<float>(j)/(frequency-1);
                float dot_top_left     = gradient_top_left.dot(normalized_j, normalized_i);
                float dot_top_right    = gradient_top_right.dot(normalized_j - 1, normalized_i);
                float dot_bottom_left  = gradient_bottom_left.dot(normalized_j, normalized_i - 1);
                float dot_bottom_right = gradient_bottom_right.dot(normalized_j - 1, normalized_i - 1);

                noisemap[(y1+i)*MAP_WIDTH+(x1+j)] = static_cast<uint16_t>(
                    smoothStep(
                        smoothStep(dot_top_left, dot_top_right,normalized_j), 
                        smoothStep(dot_bottom_left, dot_bottom_right,normalized_j),
                        normalized_i
                    ) * HEIGHT_MAP_MAX + 0b00100000
                ) & 255;
            }
        }
    }
}; 
