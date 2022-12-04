#include "Circle.hpp"

#include <cmath>

Circle Circle::CircleFromThreePoints(Point p1, Point p2, Point p3) {
    float x1 = p1.x;
    float y1 = p1.y;
    float x2 = p2.x;
    float y2 = p2.y;
    float x3 = p3.x;
    float y3 = p3.y;

    float a = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;

    float b = (x1 * x1 + y1 * y1) * (y3 - y2)
              + (x2 * x2 + y2 * y2) * (y1 - y3)
              + (x3 * x3 + y3 * y3) * (y2 - y1);

    float c = (x1 * x1 + y1 * y1) * (x2 - x3)
              + (x2 * x2 + y2 * y2) * (x3 - x1)
              + (x3 * x3 + y3 * y3) * (x1 - x2);

    float x = -b / (2 * a);
    float y = -c / (2 * a);

    return {Point(x,y), std::hypot(x - x1, y - y1)};
}

bool Circle::is_point_supported(const Point &point, float error) const {
    const float distance = std::abs(std::hypot(point.x - center.x, point.y - center.y) - radius);
    return distance < error;
}
