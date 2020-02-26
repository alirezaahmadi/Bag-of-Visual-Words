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


#include <include/utils_parser.h>
  
void writeBinaryHistImage(const std::string& file_name,
                        const std::vector<HistImage>& prod) {
std::ofstream file(file_name, std::ios::binary);
for (const HistImage& p : prod) file.write(p.name, sizeof(p));
}

std::vector<HistImage> readBinaryHistImage(const std::string& file_name) {
std::vector<HistImage> prod;
std::ifstream file(file_name, std::ios::binary);

HistImage temp;
while (file.read(
    temp.name,
    sizeof(temp)))  // for every HistImage read from the file
    prod.push_back(temp);  // add it to the vector

return prod;
}

vector<vector<uint>> hist_features(vector<HistImage>& HI, uint K) {

  vector<vector<uint>> centroids_per_image;
  std::vector<uint> tmp_hist;

  // 2D-vector with centroids per image
  cout << "Size Hist-2d-Vec: " << HI.size() << ": " << K << endl;
  for (size_t j = 0; j < HI.size(); j++) {
    for (uint i = 0; i < K; i++){
      tmp_hist.push_back(HI[j].hist[i]);
    }
    centroids_per_image.push_back(tmp_hist);
    tmp_hist.clear();
  }
  return centroids_per_image;
}

bool ImgHist_sorter(const HistImage &a, const HistImage &b) {
    if (a.CosCom > b.CosCom)
        return true;
    return false;
}