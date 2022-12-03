#ifndef CIRCLE_DETECTION_RANSAC_HPP
#define CIRCLE_DETECTION_RANSAC_HPP

#include "Circle.hpp"

class RANSAC {
public:
    RANSAC(int iteration, float error): iteration(iteration), error(error){}
private:
    int iteration;
    float error;
    Circle bestModel;
};

#endif //CIRCLE_DETECTION_RANSAC_HPP
