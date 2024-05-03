# PerlinNoise
Simple perlin noise replicating the original in cpp

Just copy what mains does to initalize your noise map

<img width="600" alt="Screenshot 2024-04-29 at 11 26 45 PM" src="https://github.com/BearnMountain/PerlinNoise/assets/161377261/67c360cd-20fe-498d-b012-0c0be444be48">



# Spaghetti Noise
Replica of perlin noise but with lattice like structure that is resultant of std::abs applying to each value before normalizing and static_casting value to "uint8_t"

initialize in main.cpp

<img width="600" alt="Screenshot 2024-04-29 at 11 40 06 PM" src="https://github.com/BearnMountain/PerlinNoise/assets/161377261/2e4c6b0e-30a8-46ba-be9c-daf591ec5f74">

# Perlin with Fractional Brownian Noise

## Set values for example
unsigned int seed = 235319234;
uint8_t octaves = 6;
float lacunarity = 0.234f;
float persistence = 0.65f;

<img width="600" alt="Screenshot 2024-05-02 at 5 08 31 PM" src="https://github.com/BearnMountain/ProceduralNoise/assets/161377261/fd8d6d4e-7d5d-49f0-8088-cb4189b0059a">
