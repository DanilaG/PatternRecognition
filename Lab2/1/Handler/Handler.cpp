#include "Handler.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <numeric>

#include "Logic/Logic.h"

Handler::Handler(unsigned int max_value, unsigned int number_attempt)
    : max_value_(max_value), number_attempt_(number_attempt) {
    distribution_series_ = get_distribution_series(max_value_, number_attempt_);
    real_distribution_series_.resize(distribution_series_.size());
}

std::vector<double> Handler::distribution_function() {
    std::vector<double> ans(distribution_series_.size());
    std::partial_sum(distribution_series_.begin(),
                     distribution_series_.end(),
                     ans.begin());
    return ans;
}

std::vector<double> Handler::real_distribution_function() {
    std::vector<double> ans(real_distribution_series_.size());
    std::partial_sum(real_distribution_series_.begin(),
                     real_distribution_series_.end(),
                     ans.begin());
    return ans;
}

Gist Handler::real_gist(unsigned int n) {
    Gist gist;
    gist.start = 0;
    gist.end = real_distribution_series_.size() + 1;
    gist.y.resize(n, 0);
    double h = (gist.end - gist.start) / n;
    unsigned int k = 1;
    for (unsigned int i = 0; i < real_distribution_series_.size(); i++) {
        while (k * h + gist.start < i) { k++; }
        gist.y[k - 1] += real_distribution_series_[i];
    }
    return gist;
}

double Handler::in_area(unsigned int first, unsigned int second) {
    return std::accumulate(distribution_series_.begin() + first,
                           distribution_series_.begin() + second + 1,
                           0.0);
}

bool Handler::generate_file(unsigned int n, std::string& name) {
    std::ofstream f(name, std::ios::out | std::ios::binary);
    if (!f) { return false; }

    auto ans = experiments_result(n, max_value_, number_attempt_);
    f.write(reinterpret_cast<const char*>(&ans[0]), sizeof(ans[0]) * ans.size());
    f.close();

    return true;
}

bool Handler::load_file(std::string& name) {
    std::ifstream f(name, std::ios::in | std::ios::binary);
    if (!f) { return false; }

    const unsigned int size = std::filesystem::file_size(name);
    std::vector<unsigned char> played_sequence(size);

    f.read(reinterpret_cast<char*>(&played_sequence[0]),
           sizeof(played_sequence[0]) * size);
    f.close();

    std::fill(real_distribution_series_.begin(),
              real_distribution_series_.end(),
              0.0);
    for (const auto& i : played_sequence) { real_distribution_series_[i]++; }

    for (auto& i : real_distribution_series_) { i /= size; }

    return true;
}

double Handler::count_analytic_average() {
    return get_average(distribution_series_);
}

double Handler::count_real_average() {
    return get_average(real_distribution_series_);
}

double Handler::count_analytic_variance() {
    return get_variance(distribution_series_);
}

double Handler::count_real_variance() {
    return get_variance(real_distribution_series_);
}

double Handler::count_analytic_asymmetry() {
    return get_asymmetry(distribution_series_);
}

double Handler::count_real_asymmetry() {
    return get_asymmetry(real_distribution_series_);
}

double Handler::count_analytic_excess() {
    return get_excess(distribution_series_);
}

double Handler::count_real_excess() {
    return get_excess(real_distribution_series_);
}
