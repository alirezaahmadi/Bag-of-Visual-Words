#pragma once

#include <include/BinLib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

class Kmeans_Flann {
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

  std::vector<Product> kmeans(vector<Product>& input_vectors, uint16_t K,
                              vector<HistImage>& histogram_Image,
                              vector<uint>& Img_SiftSize) {
    size_t nSamples = input_vectors.size();
    vector<Product> centroids;
    vector<Product> old_centroids;
    vector<cv::Mat> cluster;
    cluster.resize(K);
    cv::Mat centroid_Mat;
    vector<cv::Mat> sift_vec;
    int cnt = 0;
    int iterations = 0;

    // randomly select k samples to initialize k centroid
    for (size_t k = 0; k < K; k++) {
      int rand_int = (rand() % (uint)nSamples);
      centroids.push_back(input_vectors[rand_int]);
      old_centroids.push_back(input_vectors[rand_int]);
    }

    cerr << ">>>>>>>>>>>>> Centroids initialized <<<<<<<<<<<<<<<<<" << endl;
    cv::flann::KDTreeIndexParams indexParams(4);
    cv::Mat nearestVectorIdx(1, K, cv::DataType<int>::type);
    cv::Mat nearestVectorDist(1, K, cv::DataType<float>::type);
    for (size_t i = 0; i < nSamples; i++) {
      cv::Mat sift_(1, 128, cv::DataType<float>::type, input_vectors[i].sift);
      sift_vec.push_back(sift_);
    }
    while (true) {
      iterations++;
      cout << "******************iteration*****************: " << iterations
           << endl;
      // iteratively find better centroids
      // for every sample, find which cluster it belongs to,
      // by comparing the distance between it and each clusters' centroid.    
      // Input_vectors type Product to type Mat for Flann
      for (size_t i = 0; i < centroids.size(); i++) {
        cv::Mat centroid_vec(1, 128, cv::DataType<float>::type,
                             centroids[i].sift);  //--> CHANGED
        centroid_Mat.push_back(centroid_vec);
      }
      cv::flann::Index kdtree(centroid_Mat, indexParams);

      // Loop for Kmeans-Flann
      uint Image_counter = 0;
      uint tmp_nSamples = 0;
      for (size_t i = 0; i < nSamples; i++) {
        kdtree.knnSearch(sift_vec[i], nearestVectorIdx, nearestVectorDist, 1);
        input_vectors[i].ClusterID = nearestVectorIdx.at<uint>(0, 0);
        cluster[nearestVectorIdx.at<uint>(0, 0)].push_back(sift_vec[i]);

        if (Img_SiftSize[Image_counter] > i - tmp_nSamples) {
          histogram_Image[Image_counter]
              .hist[nearestVectorIdx.at<uint>(0, 0)]++;
        } else {
          Image_counter++;
          tmp_nSamples += Img_SiftSize[Image_counter - 1];
        }
      }
      // for every cluster, re-calculate its centroid.
      // calculate mean of every dimension for each cluster
      cv::Mat mean_;
      for (size_t k = 0; k < K; k++) {
        cv::Size size_ = cluster[k].size();
        if (size_.height != 0 && size_.width != 0) {
          cv::reduce(cluster[k], mean_, 0, CV_REDUCE_SUM,
                     cv::DataType<float>::type);

          for (int i = 0; i < 128; ++i) {
            centroids[k].sift[i] = mean_.at<float>(0, i) / size_.height;
          }
        }
      }

      // calculate distance between old and new Centroid for each cluster
      float dist[K];
      float avg_dist = 0.0;
      cnt = 0;
      for (size_t k = 0; k < K; k++) {
        dist[k] = getDistance(centroids[k], old_centroids[k]);
        avg_dist += dist[k];
      }

      cout << "Cluster Number: " << K << " -> "
           << "avg_dist: " << avg_dist / K << endl;
      if (avg_dist / K <= 20) {
        cnt = K;
      }

      old_centroids.clear();
      for (size_t i = 0; i < centroids.size(); i++) {
        old_centroids.push_back(centroids[i]);
      }

      for (size_t k = 0; k < K; k++) {
        cluster[k].release();
      }

      centroid_Mat.release();
      if (cnt == K) {
        break;
      }
    }
    cout << "******************iteration*****************: " << iterations
         << endl;
    return old_centroids;  // to do
  }
};
