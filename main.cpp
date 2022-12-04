#include <cstdlib>
#include <fmt/ranges.h>
#include <fstream>
#include <iterator>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>


#include "ransac.hpp"

void read_from_file(const char* filename, std::vector<Point>& points);
void write_to_image(const char* filename, const std::vector<Point>& points, const Circle& circle);


int main(int argc , char** argv) {
    std::vector<Point> points;
    if (argc != 4) {
        fmt::print(stderr, "Usage: cirle_detection file.text iteration error");
        return EXIT_FAILURE;
    }


    read_from_file(argv[1], points);

    if (points.empty()) {
        fmt::print(stderr, "Reading from the file was unsuccessful");
        return EXIT_FAILURE;
    }

    RANSAC ransac(std::stoi(argv[2]), std::stof(argv[3]));
    ransac.run(points);
    const Circle best = ransac.getBestModel();
    fmt::print("{}\n", best);

    write_to_image("res.png", points, best);
    return EXIT_SUCCESS;
}

void read_from_file(const char* filename,std::vector<Point>& points){
    std::ifstream inputstream(filename);
    points.assign(std::istream_iterator<Point>(inputstream), std::istream_iterator<Point>());
}

void write_to_image(const char* filename, const std::vector<Point>& points, const Circle& circle){
    cv::Mat mat = cv::Mat::zeros(1920, 2560, CV_8UC3);

    const cv::Point2f  point {circle.getCenter().x,circle.getCenter().y};
    cv::circle(mat, point, circle.getRadius(), cv::Scalar( 0, 0, 255 ));

    for (const Point &p: points) {
        cv::Vec3b pixel;
        pixel.val[0] = 255;
        pixel.val[1] = 0,
        pixel.val[1] = 0;
        mat.at<cv::Vec3b>(p.y,p.x)=pixel;
    }

    bool error = cv::imwrite(filename,mat);
}