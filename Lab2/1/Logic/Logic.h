#ifndef LAB2_1_LOGIC_H
#define LAB2_1_LOGIC_H

#include <vector>

std::vector<double> get_distribution_series(unsigned int max_value,
                                            unsigned int number_attempt);

std::vector<unsigned char> experiments_result(unsigned int n,
                                              unsigned int max_value,
                                              unsigned int number_attempt);

double get_average(const std::vector<double>& data);
double get_variance(const std::vector<double>& data);
double get_asymmetry(const std::vector<double>& data);
double get_excess(const std::vector<double>& data);

#endif  // LAB2_1_LOGIC_H
