#include "perlin.cpp"

// examples of initializing values for noisemap

Perlin* map;
const uint16_t MAP_HEIGHT = 1000;
const uint16_t MAP_WIDTH  = 1000;
uint8_t noisemap[MAP_HEIGHT][MAP_WIDTH]={{0}};
unsigned int seed = 235329234; // 9 digits seeds for randomization

int main(){
  map = new Perlin(MAP_WIDTH, MAP_HEIGHT, &noisemap[0][0], 20, seed); // populates the noisemap with 2^8 integer values
  
  return 0;
}
