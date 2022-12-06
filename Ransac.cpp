#include "Ransac.hpp"

#include <algorithm>
#include <array>

void RANSAC::run(const std::vector<Point> &dataSet) {
    for (int i = 0; i < iteration; ++i) {
        std::array<Point, sample_size> point;
        std::sample(dataSet.cbegin(), dataSet.cend(), point.begin(), sample_size, gen);

        Circle circle = Circle::CircleFromThreePoints(point);
        count_supporting_points(circle, dataSet, error);

        if (circle.getSupportedPoints() > bestModel.getSupportedPoints()){
            bestModel = circle;
        }
    }
}

void RANSAC::count_supporting_points(Circle &circle, const std::vector<Point> &dataSet, float error) {
    const int count = std::count_if(dataSet.cbegin(), dataSet.cend(), [error, &circle](const Point& point){
        return circle.is_point_supported(point, error);
    });
    circle.setSupportedPoints(count);
}
