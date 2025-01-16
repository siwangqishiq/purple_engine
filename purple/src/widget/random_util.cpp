#include "widget/random_util.h"
#include <ctime>

namespace purple{
    std::default_random_engine RandomUtil::rndEngine(time(0));

    int RandomUtil::randomInt(int min, int max){
        std::uniform_int_distribution<int> u(min , max);
        return u(rndEngine);
    }
    
    float RandomUtil::randomFloat(float min , float max){
        std::uniform_real_distribution<float> u(min, max);
        return u(rndEngine);
    }
}