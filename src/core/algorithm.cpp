#include "algorithm.h"

#include <random>

static std::mt19937 gen(std::random_device{}());

float getRandomNUmber(int start, int end){
    std::uniform_real_distribution<> dist(start, end);

    int number = dist(gen);
    return number;
}

