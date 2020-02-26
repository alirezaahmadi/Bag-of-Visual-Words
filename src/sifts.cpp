#pragma once

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "include/sifts.h"

using std::string;
using std::vector;

using cv::Mat;
using cv::KeyPoint;
using cv::DrawMatchesFlags;
using cv::Scalar;
// for Mac - openCV 3
// using cv::xfeatures2d::SiftFeatureDetector;
// using cv::xfeatures2d::SiftDescriptorExtractor;
//for linux - opencv 2
using cv::SiftFeatureDetector;
using cv::SiftDescriptorExtractor;

Mat computeSifts(const string& fileName, Mat& imageWithKeypoints) {
  const Mat input = cv::imread(fileName.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  Mat descriptors;

  // detect key points
  SiftFeatureDetector detector;
  vector<KeyPoint> keypoints;
  detector.detect(input, keypoints);

  // present the keypoints on the image
  drawKeypoints(input, keypoints, imageWithKeypoints);

  // extract the SIFT descriptors
  SiftDescriptorExtractor extractor;
  extractor.compute(input, keypoints, descriptors);
  return descriptors;
}
