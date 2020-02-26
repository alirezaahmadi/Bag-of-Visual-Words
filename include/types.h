/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

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