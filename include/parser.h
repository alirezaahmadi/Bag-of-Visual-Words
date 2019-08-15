/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#pragma once

#include <stdio.h>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace boost::filesystem;

// eliminate ".png" from file name
vector<string> FileNameSubtract(vector<string> ImageList) {
  for (size_t i = 0; i < ImageList.size(); ++i) {
    ImageList[i].erase(ImageList[i].size() - 4);
  }
  return ImageList;
}
// extracts filenames of images
vector<string> FileNamesInDirectory(string folder_name) {
  vector<string> ImageNames;
  // represent path in the filesystem (std::filesystem::path)
  path p(folder_name);
  std::cout << "Database from:  " << folder_name << std::endl;
  // directory_iterator iterates over entries of path p until there is no
  // entry anymore
  for (auto i = directory_iterator(p); i != directory_iterator(); i++) {
    string name_ = i->path().filename().string();
    // check if not a directory and if the file is a png-image
    if (!is_directory(i->path()) &&
        name_.compare(name_.size() - 3, 3, "png") == 0) {
      ImageNames.push_back(i->path().filename().string());
    } else {
      continue;
    }
  }
  std::cout << "Database Loaded" << endl;
  return ImageNames;
}
// extract the timestamps of images
vector<double> ReadTimeStampFile(string file_name) {
  std::vector<double> TimeStamp = {0};
  int cnt = 0;
  size_t l_size = 6;
  string line;
  std::ifstream infile(file_name, std::ios_base::in);
  if (!infile.is_open()) {
    std::cout << "Cant open file:  " << file_name << std::endl;
    return TimeStamp;
  } else {
    std::cout << "TimeStamps from:  " << file_name << std::endl;
    while (getline(infile, line)) {
      // save timestap as float
      TimeStamp.emplace_back(std::stod(line, &l_size));
      cnt++;
    }
    std::cout << "TimeStamps Loaded" << endl;
    return TimeStamp;
  }
}
// extract the GPS points and timestamps
vector<gps_info> ReadGpsFile(string file_name) {
  std::vector<gps_info> Pose;
  // beginnig and ending of the three elements time, lat, long in gps file
  std::string line;
  std::string line_tmp;
  size_t pos_end[3] = {75, 112, 125};
  size_t pos_begin[3] = {57, 102, 116};
  double TimeStap_ = 0.0, latitude_ = 0.0, longitude_ = 0.0;
  size_t l_size[3] = {8, 8, 8};
  int cnt = 0;
  // cpp lecture "I/O" slide 13: ios_base::in --> open file for reading
  ifstream infile(file_name, std::ios_base::in);
  if (!infile.is_open()) {
    std::cout << "Cant open file:  " << file_name << std::endl;
    return Pose;
  } else {
    std::cout << "GPS Data from:  " << file_name << std::endl;
    while (getline(infile, line)) {
      // cout << cnt << ": ";
      for (int index = 0; index < 3; index++) {
        if (index != 0 && line.at(pos_end[index]) != ',') {
          pos_end[index]--;
          pos_begin[index]--;
        } else {
          pos_end[0] = 75;
          pos_end[1] = 112;
          pos_end[2] = 125;
          pos_begin[0] = 57;
          pos_begin[1] = 102;
          pos_begin[2] = 116;
        }
        size_t pos = pos_end[index];
        // subtracting n number of characters in a line
        if (pos != string::npos) {         
          line_tmp = line.substr(0, pos);
        }
        pos = pos_begin[index];
        if (pos != string::npos) {        
          line_tmp = line_tmp.substr(pos + 1);
          if (index == 0) {
            TimeStap_ = std::stod(line_tmp, &l_size[0]);
          } else if (index == 1) {
            latitude_ = std::stod(line_tmp, &l_size[1]);
          } else if (index == 2) {
            longitude_ = std::stod(line_tmp, &l_size[2]);
          }
        }
      }
      Pose.push_back({TimeStap_, latitude_, longitude_});
      cnt++;
    }
    std::cout << "GPS Data Loaded" << endl;
    return Pose;
  }
}
// extract Hist feature estimation for each image file
