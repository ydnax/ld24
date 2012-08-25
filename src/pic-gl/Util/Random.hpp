#ifndef picppgl_Util_Random_hpp
#define picppgl_Util_Random_hpp
#include <chrono>
#include <random>

namespace picppgl{
class Random{
    std::mt19937 generator;
    Random(){
        auto time=std::chrono::high_resolution_clock::now();
        generator.seed(time);
    }
    public:
        template<class t>
        t operator() (t min, t max){
            uniform_real_distribution<t> dist(min, max);
            return dist(generator);
        }


};
static Random random;

#endif