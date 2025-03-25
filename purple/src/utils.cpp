#include "utils.h"
#include <cmath>
#include "widget/random_util.h"

namespace purple{
    std::string date_time(std::time_t posix){
        char buf[20]; // big enough for 2015-07-08 10:06:51\0
        std::tm tp = *std::localtime(&posix);
        return {buf, std::strftime(buf, sizeof(buf), "%F %T", &tp)};
    }

    long long currentTimeMicro(){
        using namespace std;
        using namespace std::chrono;
        auto now = system_clock::now();
        auto us = duration_cast<microseconds>(now.time_since_epoch());
        return us.count();
    }

    long long currentTimeMillis(){
        using namespace std;
        using namespace std::chrono;
        // get absolute wall time
        auto now = system_clock::now();
        // find the number of milliseconds
        auto ms = duration_cast<milliseconds>(now.time_since_epoch());
        return ms.count();
    }

    float currentTimeMillisFloat(){
        auto t = currentTimeMillis();
        return t / 1000.0f;
    }

    void ScaleWithPoint(Point &point , float scale, Point center){
        float x = point.x;
        float y = point.y;

        point.x = scale * x + center.x - scale * center.x;
        point.y = scale * y + center.y - scale * center.y;
    }

    void Rotate(Point &p, float cx , float cy , float angle){
        float s = sin(angle);
        float c = cos(angle);

        float x = p.x;
        float y = p.y;

        float originX = x;
        float originY = y;
        // translate point back to origin:
        originX -= cx;
        originY -= cy;

        // rotate point
        float xnew = originX * c - originY * s;
        float ynew = originX * s + originY * c;

        // translate point back:
        x = xnew + cx;
        y = ynew + cy;

        p.x = x;
        p.y = y;
    }

    float RoundToTwoDecimal(float num){
        return std::round(num * 100.0) / 100.0;
    }

    bool PointInCircle(float x , float y , float cx , float cy , float radius){
        const float dx = (cx - x);
        const float dy = (cy - y);
        return dx * dx + dy * dy <=  radius * radius;
    }

    float Clamp(float x ,float min , float max){
        if(x < min){
            return min;
        }else if(x > max){
            return max;
        }else{
            return x;
        }
    }
    
    int RndInt(int min, int max){
        return RandomUtil::randomInt(min, max);
    }

    float RndFloat(float min , float max){
        return RandomUtil::randomFloat(min, max);
    }
}