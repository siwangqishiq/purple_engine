#pragma once

#include <random>

namespace purple{
    class RandomUtil{
    public:
        static std::default_random_engine rndEngine;
        
        static void setRandomSeed(int seed);
        static int randomInt(int min, int max);
        static float randomFloat(float min, float max);
    };
}