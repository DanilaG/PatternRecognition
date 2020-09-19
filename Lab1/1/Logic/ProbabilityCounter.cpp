#include "ProbabilityCounter.h"

#include <algorithm>
#include <limits>
#include <random>
#include <stdexcept>

ProbabilityCounter::value_type ProbabilityCounter::next() {
    if (numbers_count_ >= numbers_.size()) { return -1; }

    if (is_suitable(numbers_[numbers_count_])) { suitable_count_++; }
    return numbers_[numbers_count_++];
}

double ProbabilityCounter::count(unsigned int n) {
    while (n > 0 && next() >= 0) { n--; }
    return get_probability();
}

void ProbabilityCounter::refill_numbers(unsigned int digit_capacity) {
    double pow = std::pow(10, digit_capacity);

    if (digit_capacity > std::numeric_limits<value_type>::max()) {
        std::invalid_argument("Wrong digit capacity!");
    }

    digit_capacity_ = digit_capacity;

    numbers_.resize(pow);
    for (unsigned int i = 0; i < numbers_.size(); i++) { numbers_[i] = i; }

    std::random_device rd;
    std::mt19937 g(rd());
    random_shuffle(numbers_.begin(), numbers_.end());
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

bool UniqProbabilityCounter::is_suitable(value_type number) const {
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
