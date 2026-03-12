#include "algorithm.h"

#include <random>

float getRandomNUmber(int start, int end){
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> dist(start, end);
 
    int number = dist(gen);

    return number;
}

