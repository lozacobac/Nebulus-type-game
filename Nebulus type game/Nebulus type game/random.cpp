#include "random.h"
#include <random>
int random::getRandomNumber(int min, int max)
{
    std::random_device m_rd;
    std::mt19937 m_gen(m_rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(m_gen);
}
