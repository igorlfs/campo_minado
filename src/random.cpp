#include "random.hpp"

using namespace std;

int Random::rng(const int &floor, const int &ceil) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(floor, ceil);
    return dist(rng);
}
