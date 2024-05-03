#include "perlinwithbrownian.cpp"

const uint16_t chunk = 16;
const uint16_t MAP_HEIGHT = 1024; // wants to be (2^4)*n in size, 
const uint16_t MAP_WIDTH  = 1024; // ^
uint8_t noisemap[MAP_HEIGHT][MAP_WIDTH]={{0}};
unsigned int seed = 235319234; // 9 digits seeds for xorshift


int main(){
	uint8_t octaves = 6;
  float lacunarity = 0.234f;
  float persistence = 0.65f;

  // values set in initialization so that you don't have to send float/uint8 values repetitively.
  map = new Perlin(&noisemap[0][0], MAP_WIDTH, MAP_HEIGHT,octaves, lacunarity, persistence, seed);

	for(int i=0;i<MAP_HEIGHT/16;i++){
		for(int j=0;j<MAP_WIDTH/16;j++){
			map->fillChunk16(j*15, i*15);
		}
	}
}
