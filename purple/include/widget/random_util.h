#pragma once

#include <random>

namespace purple{
    class RandomUtil{
    public:
        static int randomInt(int min, int max);
        static float randomFloat(float min, float max);
        static std::default_random_engine rndEngine;
    };
}