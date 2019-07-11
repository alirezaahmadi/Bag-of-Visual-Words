#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define ClusterNum_K 2000  // Initial -- will get update through run inputs

struct Product {
  char name[50];
  uint ClusterID;
  uint siftNum;
  bool isCentroid;
  float sift[128];
};

struct gps_info {
  // float first_num;
  double time;
  double latitude;
  double longitude;
  // float qual;
  // int sat;
  // float htop;
};

struct HistImage {
  char name[50];
  uint RowNum;
  double time;
  double latitude;
  double longitude;
  float CosCom;
  float hist[ClusterNum_K];
};

class BinIf {
 public:
  void WriteBinaryProduct(const std::string& file_name,
                          const std::vector<Product>& prod) {
    std::ofstream file(file_name, std::ios::binary);
    for (const Product& p : prod) file.write(p.name, sizeof(p));
  }

  std::vector<Product> ReadBinaryProduct(const std::string& file_name) {
    std::vector<Product> prod;
    std::ifstream file(file_name, std::ios::binary);

    Product temp;
    while (file.read(
        temp.name,
        sizeof(temp)))       // for every Product read from the file
      prod.push_back(temp);  // add it to the vector

    return prod;
  }

  void WriteBinaryHistImage(const std::string& file_name,
                            const std::vector<HistImage>& prod) {
    std::ofstream file(file_name, std::ios::binary);
    for (const HistImage& p : prod) file.write(p.name, sizeof(p));
  }

  std::vector<HistImage> ReadBinaryHistImage(const std::string& file_name) {
    std::vector<HistImage> prod;
    std::ifstream file(file_name, std::ios::binary);

    HistImage temp;
    while (file.read(
        temp.name,
        sizeof(temp)))  // for every HistImage read from the file
      prod.push_back(temp);  // add it to the vector

    return prod;
  }
};