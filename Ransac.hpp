#ifndef CIRCLE_DETECTION_RANSAC_HPP
#define CIRCLE_DETECTION_RANSAC_HPP

#include <random>
#include <vector>

#include "Circle.hpp"

class RANSAC {
public:
    RANSAC(int iteration, float error): iteration(iteration), error(error){}

    void run(const std::vector<Point>& dataSet);

    [[nodiscard]] const Circle &getBestModel() const {
        return bestModel;
    }

private:
    int iteration;
    float error;
    Circle bestModel;
    std::mt19937 gen{std::random_device{}()};
    static constexpr std::size_t sample_size = 3U;
    
    static void count_supporting_points(Circle& circle, const std::vector<Point>& dataSet, float error);
};

#endif //CIRCLE_DETECTION_RANSAC_HPP
