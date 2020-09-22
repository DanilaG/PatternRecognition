#ifndef LAB1_1_PROBABILITYCOUNTER_H
#define LAB1_1_PROBABILITYCOUNTER_H

#include <array>
#include <random>
#include <vector>

class ProbabilityCounter {
  public:
    typedef unsigned int value_type;

    ProbabilityCounter(unsigned int digit_capacity);

    value_type next();

    double count(unsigned int n);

    double get_probability() const {
        return static_cast<double>(suitable_count_) / numbers_count_;
    };

  protected:
    virtual bool is_suitable(value_type number) const = 0;

    std::array<unsigned int, 10> matches(value_type number) const;

    std::mt19937 gen_;
    std::uniform_int_distribution<value_type> dis_;
    unsigned int numbers_count_ = 0U;
    unsigned int suitable_count_ = 0U;
    unsigned int digit_capacity_ = 0U;
};

class UniqueProbabilityCounter : public ProbabilityCounter {
  public:
    UniqueProbabilityCounter(unsigned int digit_capacity)
        : ProbabilityCounter(digit_capacity) {}

  protected:
    bool is_suitable(value_type number) const override final;
};

class PairProbabilityCounter : public ProbabilityCounter {
  public:
    using ProbabilityCounter::ProbabilityCounter;

  protected:
    bool is_suitable(value_type number) const override final;
};

class DoublePairProbabilityCounter : public ProbabilityCounter {
  public:
    using ProbabilityCounter::ProbabilityCounter;

  protected:
    bool is_suitable(value_type number) const override final;
};

class TripletProbabilityCounter : public ProbabilityCounter {
  public:
    using ProbabilityCounter::ProbabilityCounter;

  protected:
    bool is_suitable(value_type number) const override final;
};

#endif  // LAB1_1_PROBABILITYCOUNTER_H
