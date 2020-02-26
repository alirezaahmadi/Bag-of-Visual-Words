/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    A Host implementation of Bag of Visual Words        %
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% alirezaahmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#pragma once

#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "include/sifts.h"
#include "include/utils_parser.h"

using namespace std;
using namespace boost::filesystem;

int main() {
  // const char* const file_name = "Updated_Sifts.bin";
  string name  = "test_file";
  const char* const file_name = ("../sifts/" + name + ".bin").c_str();
  cerr << file_name << endl;
  {
    std::vector<Product> prod{Product{"alireza", 20, 1, false, {1}},
                              Product{"pourya", 10, 2, true, {0}}};
    for (int i = 0; i < 128; i++) {
      prod[0].sift[i] = 1.1 * i;
    }
    for (int i = 0; i < 128; i++) {
      prod[1].sift[i] = 2.1 * i;
    }
    writeBinaryProduct(file_name, prod);
    std::cout << "Write Done!! \n";
  }
  {
    std::vector<Product> prod = readBinaryProduct(file_name);
    for (const Product& p : prod) {
      std::cout << p.name << "  " << p.ClusterID << "  " << p.isCentroid
                << "  " << p.siftNum << std::endl;
      for (int i = 0; i < 128; i++) {
        std::cout << p.sift[i];
        std::cout << '\n';
      }
    }
  }

  // {
  //   int i = 0;
  //   size_t l_size = 6;
  //   std::vector<float> TimeStamp;
  //   string file_name = "../data1/image-imageNamesList.txt";
  //   std::string line;
  //   std::ifstream infile(file_name, std::ios_base::in);
  //   if (!infile.is_open()) {
  //     std::cout << "Cant open file:  " << file_name << std::endl;
  //     return 1;
  //   } else {
  //     std::cout << "Open file:  " << file_name << std::endl;
  //     while (getline(infile, line)) {
  //       std::cout << line << std::endl;
  //       TimeStamp.emplace_back(
  //           std::stof(line, &l_size));
  //       std::cout <<  "TS " << i << ":" << TimeStamp[i] << std::endl;
  //       i++;
  //     }
  //   }
  // }

  // {
  //   struct gps_info {
  //       float first_num;
  //       float time;
  //       float latitude;
  //       float longitude;
  //       float qual;
  //       int sat;
  //       float htop;
  //   };
  //   std::vector<gps_info> Pose;
  //   string file_name = "../data1/gps_info.txt";
  //   std::ifstream infile(file_name, std::ios_base::in);
  //   if (!infile.is_open()) {
  //     std::cout << "Cant open file:  " << file_name << std::endl;
  //     return 1;
  //   } else {
  //       size_t pos_end[3] ={75,112,125};
  //       size_t pos_begin[3] ={57,102,116};
  //       std::cout << "Open file:  " << file_name << std::endl;
  //       int cnt=0;
  //       std::string line;
  //       std::string line_tmp;
  //       while (getline(infile, line))
  //       {
  //         cout <<  cnt << ": ";
  //           for(int index=0;index<3;index++){
  //               if(index != 0 && line.at(pos_end[index])!=','){
  //                 cout << "Comma: "<< line.at(pos_end[index])<< endl;
  //                 pos_end[index]--;
  //                 pos_begin[index]--;
  //               }else{
  //                 pos_end[0] = 75;  pos_end[1] = 112;  pos_end[2] = 125;
  //                 pos_begin[0] = 57;pos_begin[1] = 102;pos_begin[2] = 116;
  //               }
  //               size_t pos =pos_end[index];
  //               if (pos != string::npos)
  //               {
  //                line_tmp = line.substr(0, pos);
  //               }
  //               pos =pos_begin[index];
  //               if (pos != string::npos)
  //               {
  //                line_tmp = line_tmp.substr(pos + 1);
  //                if(index == 0)cout << "time: "<< pos_begin[index] << "  " <<
  //                pos_end[index] << "  " << line_tmp << endl;
  //                else if(index == 1)cout << "lat: "<< pos_begin[index] << "
  //                " << pos_end[index] << "  " << line_tmp << endl;
  //                else if(index == 2)cout << "long: "<< pos_begin[index] << "
  //                " << pos_end[index] << "  " << line_tmp << endl;
  //               }
  //           }
  //           cnt++;
  //           //if(cnt == 48)break;
  //       }
  //   }
  // }
}

// if (!image.data) {
//   printf("No image data \n");
//   return -1;
// }
// namedWindow("Window Name", WINDOW_AUTOSIZE);
// imshow("Window Name", image);

// for (int row = 0; row < descriptors.rows; row++) {
//   std::vector<BinaryInterface::Product> prod = bin.ReadBinary(file_name);
//   // for (const BinaryInterface::Product& p : prod) {
//   //   std::cout << p.name << ' ' << p.siftNum;
//   //   for (int i = 0; i < 128; ++i) {
//   //     std::cout << p.sitf[i] << " ";
//   //   }
//   //   std::cout << '\n';
//   // }
// }
// if (0 < prod.size()) cout << "Read Done";