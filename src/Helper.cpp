#include "../include/NEAT/Helper.hpp"

namespace NEAT {

  unsigned int Seed::getSeed() {
    return seed;
  }
  void Seed::setSeed(unsigned int newSeed = -1) {
    if (newSeed == -1)
      seed = std::random_device()();
    else
      seed = newSeed;
    gen.seed(seed);
  }

  std::mt19937& Seed::getGenerator() {
    return gen;
  }

  unsigned int Seed::seed = std::random_device()();
  std::mt19937 Seed::gen(Seed::seed);
  // 

}
