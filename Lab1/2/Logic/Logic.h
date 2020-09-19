#ifndef LAB1_2_LOGIC_H
#define LAB1_2_LOGIC_H

struct Point {
  public:
    double x;
    double y;
};

class Circle {
  public:
    Point center;
    double r;
};

double dist(const Point &a,const Point &b = {0, 0});

double calculate_probability(const Circle &circle, unsigned int attempt);

#endif  // LAB1_2_LOGIC_H
