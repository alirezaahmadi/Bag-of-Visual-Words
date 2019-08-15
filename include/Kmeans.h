/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#pragma once

#include <include/BinLib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Kmeans {
 public:

  float getDistance(Product& Centroid, Product& sample) {
    float Sum[128];
    float result = 0.0;
    for (int i = 0; i < 128; ++i) {
      Sum[i] = Centroid.sift[i] - sample.sift[i];
    }
    for (int i = 0; i < 128; ++i) {
      result += pow(Sum[i], 2);
    }
    return sqrt(result);
  }

  int getNearestCentroid(vector<Product>& centroids, Product& sample) {
    double minDistance = 0;
    int minLabel = 0;
    for (size_t i = 0; i < centroids.size(); i++) {
      double tempDistance = getDistance(centroids[i], sample);
      if (i == 0 || tempDistance < minDistance) {
        minDistance = tempDistance;
        // index of the nearest centroid
        minLabel = i;
      }
    }
    return minLabel;
  }

  bool kmeans(vector<Product>& input_vectors, uint16_t K) {
    size_t nSamples = input_vectors.size();
    // randomly select k samples to initialize k centroid
    vector<Product> centroids;
    Product Centroid_tmp;
    for (size_t k = 0; k < K; k++) {
      int rand_int = rand() % nSamples;
      input_vectors[rand_int].isCentroid = true;
      centroids.push_back(input_vectors[rand_int]);
    }
    // iteratively find better centroids
    vector<vector<Product>> cluster;
    {
      cluster.resize(K);
      // for every sample, find which cluster it belongs to,
      // by comparing the distance between it and each clusters' centroid.
      for (size_t m = 0; m < nSamples; m++) {
        int which = getNearestCentroid(centroids, input_vectors[m]);
        cluster[which].emplace_back(input_vectors[m]);
      }
      // for every cluster, re-calculate its centroid.
      // calculate mean of every dimension for each cluster
      float index_sum = 0.0;
      centroids.clear();
      for (size_t k = 0; k < K; k++) {
        for (size_t m = 0; m < 128; m++) {
          for (size_t n = 0; n < cluster[k].size(); n++) {
            index_sum += cluster[k][n].sift[m];
          }
          index_sum /= cluster[k].size();
          Centroid_tmp.sift[m] = index_sum;
          cout << index_sum  << " " << cluster[k].size() << endl;
          index_sum =0;
        }
        float tmp_dist_old = getDistance(input_vectors[0], Centroid_tmp);
        for (size_t i = 1; i < nSamples; ++i) {
          float tmp_dist = getDistance(input_vectors[i], Centroid_tmp);
          if (tmp_dist_old > tmp_dist) {
            centroids[k] = input_vectors[i];
            cout << tmp_dist << endl;
            if (abs(tmp_dist_old - tmp_dist) < 5) {
              input_vectors[i].isCentroid = true;
              cout << "*****its Centroid*****" << endl;
              break;
            }
          } else if (input_vectors[i].isCentroid == true) {
            input_vectors[i].isCentroid = false;
          }
        }
      }
    }
    return true; 
  }
};
