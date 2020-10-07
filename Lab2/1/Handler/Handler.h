#ifndef LAB2_1_HANDLER_H
#define LAB2_1_HANDLER_H

#include <string>
#include <vector>

struct Gist {
    std::vector<double> y;
    double start;
    double end;
};

class Handler {
  public:
    Handler(unsigned int max_value, unsigned int number_attempt);

    std::vector<double> distribution_series() { return distribution_series_; };
    std::vector<double> real_distribution_series() {
        return real_distribution_series_;
    };
    std::vector<double> distribution_function();
    std::vector<double> real_distribution_function();
    Gist real_gist(unsigned int n);

    double in_area(unsigned int first, unsigned int second);

    bool generate_file(unsigned int n, std::string& name);
    bool load_file(std::string& name);

    double count_analytic_average();
    double count_real_average();
    double count_analytic_variance();
    double count_real_variance();
    double count_analytic_asymmetry();
    double count_real_asymmetry();
    double count_analytic_excess();
    double count_real_excess();

  protected:
    const unsigned int max_value_;
    const unsigned int number_attempt_;
    std::vector<double> distribution_series_;
    std::vector<double> real_distribution_series_;
};

#endif  // LAB2_1_HANDLER_H
