#ifndef CIRCLE_DETECTION_CIRCLE_HPP
#define CIRCLE_DETECTION_CIRCLE_HPP

#include "Point.hpp"

#include <limits>
#include <cmath>
#include <array>
constexpr static int int_min = std::numeric_limits<int>::min();

class Circle {
public:
    Circle(): radius(0.F), supported_points(int_min){}
    Circle(Point center, float radius): center(center), radius(radius), supported_points(int_min){}


    static Circle CircleFromThreePoints(const std::array<Point, 3> &arr){
       return CircleFromThreePoints(arr[0], arr[1], arr[2]);
    }
    static Circle CircleFromThreePoints(Point p1, Point p2, Point p3) {
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

    [[nodiscard]] const Point &getCenter() const {
        return center;
    }

    [[nodiscard]] float getRadius() const {
        return radius;
    }

    [[nodiscard]] int getSupportedPoints() const {
        return supported_points;
    }

    void setSupportedPoints(int supportedPoints) {
        supported_points = supportedPoints;
    }


    [[nodiscard]] bool is_point_supported(const Point &point, float error) const {
        const float distance = std::abs(std::hypot(point.x - center.x, point.y - center.y) - radius);
        return distance < error;
    }


private:
    Point center;
    float radius;
    int supported_points;
};

template <> struct fmt::formatter<Circle> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Circle& circle, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "(center: {}, radius: {}, supported points: {})", circle.getCenter(),
                              circle.getRadius(), circle.getSupportedPoints());
    }
};

#endif //CIRCLE_DETECTION_CIRCLE_HPP
