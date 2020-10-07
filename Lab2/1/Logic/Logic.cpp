#include "Logic.h"

#include <cmath>
#include <iostream>
#include <random>

static void count_occurrence(std::vector<unsigned int>& ans,
                             unsigned int sum,
                             unsigned int attempt,
                             unsigned int max_value) {
    if (attempt == 0) {
        ans[sum]++;
        return;
    }
    for (unsigned int i = 0; i <= max_value; i++) {
        count_occurrence(ans, sum + i, attempt - 1, max_value);
    }
}

std::vector<double> get_distribution_series(unsigned int max_value,
                                            unsigned int number_attempt) {
    std::vector<unsigned int> occurrence(max_value * number_attempt + 1, 0);
    count_occurrence(occurrence, 0, number_attempt, max_value);

    const double number_occurrence = pow(max_value + 1, number_attempt);
    std::vector<double> ans(occurrence.size());
    for (unsigned int i = 0; i < occurrence.size(); i++) {
        ans[i] = occurrence[i] / number_occurrence;
    }

    return ans;
}

double get_average(const std::vector<double>& data) {
    double ans = 0;
    for (unsigned int i = 0; i < data.size(); i++) { ans += data[i] * i; }
    return ans;
}

static double count_moment(const std::vector<double>& data, unsigned int k) {
    double ans = 0;
    const double average = get_average(data);
    for (unsigned int i = 0; i < data.size(); i++) {
        ans += data[i] * pow(i - average, k);
    }
    return ans;
}

double get_variance(const std::vector<double>& data) {
    return count_moment(data, 2);
}

double get_asymmetry(const std::vector<double>& data) {
    double k = get_variance(data);
    return count_moment(data, 3) / (k * k * k);
}

double get_excess(const std::vector<double>& data) {
    double k = get_variance(data);
    return count_moment(data, 4) / (k * k * k * k) - 3;
}

std::vector<unsigned char> experiments_result(unsigned int n,
                                              unsigned int max_value,
                                              unsigned int number_attempt) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, max_value);
    std::vector<unsigned char> ans(n, 0);

    for (auto &i : ans) {
        for (unsigned int k = 0; k < number_attempt; k++) { i += dis(gen); }
    }

    return ans;
}
