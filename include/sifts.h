#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>
//for linux - openCV 2
#include <opencv2/nonfree/nonfree.hpp>
// for Mac - openCV 3
// #include <opencv2/xfeatures2d.hpp>

cv::Mat computeSifts(const std::string& fileName,
                     cv::Mat& imageWithKeypoints);
