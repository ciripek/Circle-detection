#include <fmt/ranges.h>
#include <fstream>
#include <iterator>
#include <vector>

#include "ransac.hpp"

void read_from_file(const char* filename, std::vector<Point>& points);


int main(int argc , char** argv) {
    std::vector<Point> points;
    if (argc != 2) {
        fmt::print(stderr, "Usage: cirle_detection file.text");
    }


    read_from_file(argv[1], points);

    if (points.empty()) {
        fmt::print(stderr, "Reading from the file was unsuccessful");
    }

    RANSAC ransac(100000, 0.5);
    ransac.run(points);
    const Circle best = ransac.getBestModel();
    fmt::print("{}\n", best);

    return 0;
}

void read_from_file(const char* filename,std::vector<Point>& points){
    std::ifstream inputstream(filename);
    points.assign(std::istream_iterator<Point>(inputstream), std::istream_iterator<Point>());
}