#ifndef CIRCLE_DETECTION_RANSAC_HPP
#define CIRCLE_DETECTION_RANSAC_HPP

#include <algorithm>
#include <array>
#include <random>
#include <vector>

#include "Circle.hpp"

class RANSAC {
public:
    RANSAC(int iteration, float error): iteration(iteration), error(error){}

    void run(const std::vector<Point>& dataSet){
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
private:
    int iteration;
    float error;
    Circle bestModel;
    std::mt19937 gen{std::random_device{}()};
    static constexpr std::size_t sample_size = 3U;
    
    static void count_supporting_points(Circle& circle, const std::vector<Point>& dataSet, float error) {
        int count = std::count_if(dataSet.cbegin(), dataSet.cend(), [error, &circle](const Point& point){
            return circle.is_point_supported(point, error);
        });
        circle.setSupportedPoints(count);
    }
};

#endif //CIRCLE_DETECTION_RANSAC_HPP
