#include "../include/NEAT/Helper.hpp"

namespace NEAT {

  unsigned int Seed::getSeed() {
    return seed;
  }
  void Seed::setSeed(unsigned int newSeed) {
    seed = newSeed;
    gen.seed(seed);
  }

  std::mt19937& Seed::getGenerator() {
    return gen;
  }

  unsigned int Seed::seed = std::random_device()();
  std::mt19937 Seed::gen(Seed::seed);
  // 
  // 
  void setRandomSeed() {
    Seed::setSeed(std::random_device()());
  }
  void setSeed(unsigned int newSeed) {
    Seed::setSeed(newSeed);
  }

  unsigned int getSeed() {
    return Seed::getSeed();
  }

}
