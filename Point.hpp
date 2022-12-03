#ifndef CIRCLE_DETECTION_POINT_H
#define CIRCLE_DETECTION_POINT_H
#include <iostream>
#include <fmt/format.h>

class Point {
public:
    float x, y;
    Point(float x = 0.0, float y = 0.0): x(x), y(y){}

    friend std::istream& operator>>(std::istream& is, Point& obj){
        is >> obj.x >> obj.y;
        return is;
    }

    friend std::ostream& operator>>(std::ostream& os, Point& obj){
        os << "Point(" << obj.x<< ", " << obj.y<< ")";
        return os;
    }
};

template <> struct fmt::formatter<Point> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Point& p, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "(x: {}, y: {})", p.x, p.y);
    }
};



#endif //CIRCLE_DETECTION_POINT_H
