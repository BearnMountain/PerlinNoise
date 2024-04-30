#include "perlin.cpp"
#include "spaghetticlattices.cpp"

// examples of initializing values for noisemap
const uint16_t MAP_HEIGHT = 1000;
const uint16_t MAP_WIDTH  = 1000;
cosnt uint8_t frequency = 20; // dictates detail, larger number means larger area to smoothly transition through.
uint8_t noisemap[MAP_HEIGHT][MAP_WIDTH]={{0}};
unsigned int seed = 235329234; // 9 digits seeds for randomization



// noise maps

SpagettiLattices* map_spaghetti;
Perlin* map_perlin;

int main(){
  map_perlin    =           new Perlin(MAP_WIDTH, MAP_HEIGHT, &noisemap[0][0], frequency, seed); // populates the noisemap with 2^8 integer values
  map_spaghetti = new SpagettiLattices(MAP_WIDTH, MAP_HEIGHT, &noisemap[0][0], frequency, seed);

  
  return 0;
}
