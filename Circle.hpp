//
// Created by bence on 2022.11.30..
//

#ifndef CIRCLE_DETECTION_CIRCLE_HPP
#define CIRCLE_DETECTION_CIRCLE_HPP

#include "Point.hpp"

#include <limits>
#include <cmath>

constexpr static int int_min = std::numeric_limits<int>::min();

class Circle {
public:
    Circle(): radius(0.F), supported_points(int_min){}
    Circle(Point center, float radius): center(center), radius(radius), supported_points(int_min){}

    [[nodiscard]] const Point &getCenter() const {
        return center;
    }

    [[nodiscard]] float getRadius() const {
        return radius;
    }

    [[nodiscard]] int getSupportedPoints() const {
        return supported_points;
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
