#include "Rand.h"
#include <random>

Rand::Rand() : gen(std::random_device{}()) {

}

int Rand::random(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double Rand::frandom(double min, double max) {
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

