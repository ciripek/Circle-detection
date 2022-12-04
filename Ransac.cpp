#include "Ransac.hpp"

#include <algorithm>
#include <array>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

void RANSAC::run(const std::vector<Point> &dataSet) {
    boost::asio::thread_pool threadPool;

    for (int i = 0; i < iteration; ++i) {
        boost::asio::post([this, &dataSet](){
            std::array<Point, sample_size> point;
            mutex.lock();
            std::sample(dataSet.cbegin(), dataSet.cend(), point.begin(), sample_size, gen);
            mutex.unlock();

            Circle circle = Circle::CircleFromThreePoints(point);
            count_supporting_points(circle, dataSet, error);

            const std::lock_guard<std::mutex>  scoped_lock(mutex);
            if (circle.getSupportedPoints() > bestModel.getSupportedPoints()){
                bestModel = circle;
            }
        });
    }

    threadPool.join();
}

void RANSAC::count_supporting_points(Circle &circle, const std::vector<Point> &dataSet, float error) {
    int count = std::count_if(dataSet.cbegin(), dataSet.cend(), [error, &circle](const Point& point){
        return circle.is_point_supported(point, error);
    });
    circle.setSupportedPoints(count);
}
