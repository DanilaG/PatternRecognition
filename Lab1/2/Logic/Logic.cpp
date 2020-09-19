#include "Logic.h"

#include <random>

double dist(const Point& a, const Point& b) {
    Point delta = {b.x - a.x, b.y - a.y};
    return sqrt(delta.x * delta.x + delta.y * delta.y);
}

double calculate_probability(const Circle& circle, unsigned int attempt) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-circle.r, circle.r);

    unsigned int line_less_radius = 0;

    for (unsigned int line_counter = 0; line_counter < attempt;
         line_counter++) {
        double x = dis(gen);
        double y = sqrt(circle.r * circle.r - x * x);

        if (dist({x, y}, {x, -y}) < circle.r) { line_less_radius++; }
    }

    return static_cast<double>(line_less_radius) / attempt;
}
