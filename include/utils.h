/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#pragma once


#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

vector<vector<float>> tfIdf(vector<vector<uint>>& centroids_per_image) {
  vector<vector<float>> tf_idf(centroids_per_image.size(),
                               vector<float>(centroids_per_image[0].size()));

  size_t number_centroids = centroids_per_image[0].size();
  size_t number_images = centroids_per_image.size();

  vector<float> images_with_centroids;
  images_with_centroids.resize(number_centroids, 0);

  vector<float> features_in_image;
  features_in_image.resize(number_images, 0);

  // vector that stores how many centroids are in an image
  for (size_t i = 0; i < number_images; i++) {
    for (size_t j = 0; j < number_centroids; j++) {
      features_in_image[i] += centroids_per_image[i][j];
    }
  }

  // vector that stores how many images has one centroid
  for (size_t i = 0; i < number_centroids; i++) {
    for (size_t j = 0; j < number_images; j++) {
      if (centroids_per_image[j][i] > 0) {
        images_with_centroids[i] += 1.0;
      }
    }
  }

  float tmp_log = 0.0;
  float result = 0.0;
  for (size_t i = 0; i < number_images; i++) {
    for (size_t j = 0; j < number_centroids; j++) {
      tmp_log = (uint)number_images / images_with_centroids[i];
      result = log(tmp_log);
      tf_idf[i][j] =
          (centroids_per_image[i][j] / features_in_image[i]) * result;
    }
  }
  cout << " tf_idf done ... " << endl;
  return tf_idf;
}
vector<float> cosine_comparison(vector<vector<float>>& hist_1, vector<float>& hist_2) {
  vector<float> comparison;
  float sum_ab = 0.0;
  float sum_a = 0.0;
  float sum_b = 0.0;
  float result = 0.0;

  for (size_t i = 0; i < hist_1.size(); i++) {
    for (size_t j = 0; j < hist_2.size(); j++) {
      
      sum_ab += hist_1[i][j] * hist_2[j];
      sum_a  += pow(hist_1[i][j], 2);
      sum_b  += pow(hist_2[j], 2);
    }
    result = sum_ab / (std::sqrt(sum_a) * std::sqrt(sum_b));
    comparison.push_back(result);

    sum_a = 0.0;
    sum_b = 0.0;
    sum_ab = 0.0;
  }
  cout << " cosine_comparison done ... " << endl;
  return comparison;
}
