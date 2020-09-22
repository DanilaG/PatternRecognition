#include "ProbabilityCounter.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

ProbabilityCounter::ProbabilityCounter(unsigned int digit_capacity)
    : digit_capacity_(digit_capacity), gen_(std::random_device()()) {
    double power = pow(10, digit_capacity_);
    dis_ = std::uniform_int_distribution<value_type>(0, power);
}

ProbabilityCounter::value_type ProbabilityCounter::next() {
    value_type number = dis_(gen_);
    if (is_suitable(number)) { suitable_count_++; }
    numbers_count_++;
    return number;
}

double ProbabilityCounter::count(unsigned int n) {
    while (n > 0 && next() >= 0) { n--; }
    return get_probability();
}

std::array<unsigned int, 10> ProbabilityCounter::matches(
    value_type number) const {
    std::array<unsigned int, 10> counter;
    std::fill(counter.begin(), counter.end(), 0);

    for (unsigned int i = 0; i < digit_capacity_; i++) {
        counter[number % 10]++;
        number /= 10;
    }

    return counter;
}

bool UniqueProbabilityCounter::is_suitable(value_type number) const {
    auto figures_count = matches(number);
    return std::count_if(figures_count.begin(),
                         figures_count.end(),
                         [](unsigned int i) { return 1 == i; }) ==
           digit_capacity_;
}

bool PairProbabilityCounter::is_suitable(value_type number) const {
    auto figures_count = matches(number);
    return 1 == std::count(figures_count.begin(), figures_count.end(), 2);
}

bool DoublePairProbabilityCounter::is_suitable(value_type number) const {
    auto figures_count = matches(number);
    return 2 == std::count(figures_count.begin(), figures_count.end(), 2);
}

bool TripletProbabilityCounter::is_suitable(value_type number) const {
    auto figures_count = matches(number);
    return 1 == std::count(figures_count.begin(), figures_count.end(), 3);
}
