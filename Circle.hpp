#ifndef CIRCLE_DETECTION_CIRCLE_HPP
#define CIRCLE_DETECTION_CIRCLE_HPP

#include <array>
#include <limits>

#include "Point.hpp"

constexpr static int int_min = std::numeric_limits<int>::min();

class Circle {
public:
    Circle(): radius(0.F), supported_points(int_min){}
    Circle(Point center, float radius): center(center), radius(radius), supported_points(int_min){}


    static Circle CircleFromThreePoints(const std::array<Point, 3> &arr){
       return CircleFromThreePoints(arr[0], arr[1], arr[2]);
    }
    static Circle CircleFromThreePoints(Point p1, Point p2, Point p3);

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


    [[nodiscard]] bool is_point_supported(const Point &point, float error) const;


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
