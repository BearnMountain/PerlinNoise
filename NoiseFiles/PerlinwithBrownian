#include <cstdlib>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

class Perlin{
public:
    uint8_t frequency; // determines the size of each "chunk", chunks are still 16x16
    unsigned int seed;
    uint16_t DEPTH_MAX = 255; // 0 x 1111 1111, determines the max elivation of the map 
    uint8_t* noisemap;
    uint16_t MAP_WIDTH;
    uint16_t MAP_HEIGHT;

    const uint8_t chunk_size = 16;

    uint8_t octaves;  // how many times I want to calculate the chunk Im rendering
    float lacunarity;
    float persistence;

    Perlin(uint8_t* noisemap, const uint16_t MAP_WIDTH, const uint16_t MAP_HEIGHT, const uint8_t octaves, const float lacunarity, const float persistence, const unsigned int seed)
    : noisemap(noisemap), MAP_WIDTH(MAP_WIDTH),  MAP_HEIGHT(MAP_HEIGHT), octaves(octaves), lacunarity(lacunarity), persistence(persistence), seed(seed){
    }
    ~Perlin(){}

    void fillChunk16(uint32_t x1, uint32_t y1){
        // gets the corners of the map
        vector2 gradient_top_left     = randomgradient(x1+y1*MAP_WIDTH);
        vector2 gradient_top_right    = randomgradient((x1+chunk_size-1)+y1*MAP_WIDTH);
        vector2 gradient_bottom_left  = randomgradient(x1+(y1+chunk_size-1)*MAP_WIDTH);
        vector2 gradient_bottom_right = randomgradient((x1+chunk_size-1)+(y1+chunk_size-1)*MAP_WIDTH);

        for(uint8_t i=0;i<chunk_size;i++){
            for(uint8_t j=0;j<chunk_size;j++){
                float normalized_i     = static_cast<float>(i)/(chunk_size-1);
                float normalized_j     = static_cast<float>(j)/(chunk_size-1);

                float dot_top_left     = gradient_top_left.dot(normalized_j, normalized_i);
                float dot_top_right    = gradient_top_right.dot(normalized_j - 1, normalized_i);
                float dot_bottom_left  = gradient_bottom_left.dot(normalized_j, normalized_i - 1);
                float dot_bottom_right = gradient_bottom_right.dot(normalized_j - 1, normalized_i - 1);

                float noise = smoothStep(
                        smoothStep(dot_top_left, dot_top_right,normalized_j), 
                        smoothStep(dot_bottom_left, dot_bottom_right,normalized_j),
                        normalized_i
                    );

                noisemap[(y1+i)*MAP_WIDTH+(x1+j)] = static_cast<uint8_t>(
                    (fractionalBrownianNoise(noise)+1)/2 * DEPTH_MAX
                );
            }
        }
    }

private:
    struct vector2{
        float x, y;
        vector2(float x, float y) : x(x),y(y){}
        float dot(float x1, float y1){ return x*x1+y*y1; }
    };

    float fractionalBrownianNoise(float noise){
        float total = 0.0f;
        float frequency = 1.0f;
        float amplitude = 1.0f;
        float maxValue = 0.0f;

        for(int i=0;i<octaves;i++){
            total += noise * amplitude;
            maxValue += amplitude;
            amplitude *= persistence;
            frequency *= lacunarity;
        }

        return total/maxValue;
    }

    vector2 randomgradient(unsigned int val){
        // XorShift algorithm for random numbers
        unsigned int random = seed+val;
        random ^= (random<<13);
        random ^= (random>>14);
        random ^= (random<<8);

        uint8_t amplitude = 2;

        return vector2(std::cos((random>>2)*amplitude), std::sin((random<<1)*amplitude)); // shift is arbituary but reduces overlap
    }

    float smoothStep(float a, float b, float normalized_step){ // returns a value between a inclusive and b inclusive
        return a + (b-a) * (3 - 2*normalized_step)*normalized_step*normalized_step;
    }
}; 
