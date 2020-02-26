/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    A Host implementation of Bag of Visual Words        
% by: Alireza Ahmadi and Robin Steffens  
% Alireza.Ahmadi@uni-bonn.de
% Robin.Steffens@gmx.net                                   
% University of Bonn- MSc Robotics & Geodetic Engineering                  
% alirezaahmadi.xyz                                      
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <include/Kmeans_Flann.h>
#include <include/utils_html.h>
#include <include/utils_parser.h>
#include <include/sifts.h>
#include <include/utils.h>

using namespace boost::filesystem;
using namespace cv;
using namespace std;


int main(int argc, char **argv) {
  if (argc >= 2) {

    std::vector<Product> prod;
    Kmeans_Flann KmeansFLANN;
    uint fileNum = 0;

    vector<string> ImageNames = getImageNames("../data1");
    // for (size_t i = 0; i < ImageNames.size(); i++) {
    //   cout << ImageNames[i] << endl;
    // }
    vector<string> ImageNameList = modifyImageNames(ImageNames);
    // for (size_t i = 0; i < ImageNameList.size(); i++) {
    //   cout << ImageNameList[i] << endl;
    // }
    // freopen("output.txt", "w", stdout);
    vector<double> time_stamp = readTimeStamps("../data1/image-timestamps.txt");
    // for (size_t i = 0; i < 10; i++) {
    //   cout << std::setprecision(20) << time_stamp[i] << endl;
    // }
    vector<gps_info> gps_info_vec = readGPSPositions("../data1/gps_info.txt");
    // for (auto i = 0; i != 10; i++) {
    //   std::cout << gps_info_vec[i].time << " ";
    //   std::cout << gps_info_vec[i].latitude << " ";
    //   std::cout << gps_info_vec[i].longitude << " " << endl;
    // }


    float time_diff = 1000;
    float time_diff_old = 1000;
    size_t start_gps = 1;
    vector<gps_info> gps_image;
    for (size_t i = 1; i < time_stamp.size(); i++){
      for (size_t j = start_gps; start_gps < gps_info_vec.size(); j++){
        time_diff = abs(time_stamp[i] - gps_info_vec[j].time);
        if (time_diff > time_diff_old){
          gps_info tmp_gps = {gps_info_vec[j-1].time, gps_info_vec[j-1].latitude, gps_info_vec[j-1].longitude};
          gps_image.push_back(tmp_gps);
          start_gps = j-1;
          i+=9;
          time_diff_old = 1000;
          break;
        }else{
          time_diff_old = time_diff;
        }
      }
    }

    if ((argc == 4 && stoi(argv[3]) == 0) || argc == 2) {
      fileNum = ImageNames.size();
    } else if (argc >= 4 && stoi(argv[3]) != 0) {
      fileNum = stoi(argv[3]);
    } else if (argc == 2 && stoi(argv[1]) == 1) {
      // dataset ....
    } else {
      cout << "Inputs don't match !!!" << endl;
      cout << "your input: " << argc << " " << stoi(argv[1]) << " "
           << stoi(argv[2]) << " " << stoi(argv[3]) << endl;
      return 0;
    }
    #undef ClusterNum_K
    #define ClusterNum_K stoi(argv[2])
    vector<HistImage> Img_Hist;
    vector<HistImage> inp_Hist{HistImage{"Empty", 0, 0.0, 0.0, 0.0, 0.0, {0.0}}};
    HistImage tmp_histogram{"Empty", 0, 0.0, 0.0, 0.0, 0.0, {0.0}};
    for (uint i = 0; i < fileNum; ++i) {
      Img_Hist.push_back(tmp_histogram);
    }

    if (1 == stoi(argv[1])) {
      cout << "dataset ...." << endl;
      Mat descriptorImage;
      Product tmp{"Empty", 0, 0, false, {0}};
      for (size_t i = 0; i < ImageNameList.size(); ++i) {
        cout << "../data1/" + ImageNames[i] << endl;
        Mat descriptors =
            computeSifts("../data1/" + ImageNames[i], descriptorImage);

        const string file_name = "../sifts/" + ImageNameList[i] + ".bin";
        cerr << file_name << endl;
        // products get loaded
        for (int row = 0; row < descriptors.rows; row++) {
          for (int col = 0; col < descriptors.cols; col++) {
            tmp.sift[col] = descriptors.at<float>(row, col);
          }
          strcpy(tmp.name, ImageNameList[i].c_str());
          tmp.siftNum = row;
          tmp.isCentroid = false;
          prod.push_back(tmp);
        }
        writeBinaryProduct(file_name, prod);
        prod.clear();
      }
    } else if (2 == stoi(argv[1])) {  
      cout << "Kmeans ...." << endl;
      // freopen("output.txt", "w", stdout);
      std::vector<uint> Img_SiftSize;

      for (size_t i = 0; i < fileNum; ++i) {  // ImageNames.size()
        // cout << "../data1/" + ImageNames[i] << endl;
        const string file_name = "../sifts/" + ImageNameList[i] + ".bin";
        std::vector<Product> tmp_prod = readBinaryProduct(file_name);
        prod.insert(prod.end(), tmp_prod.begin(), tmp_prod.end());
        Img_SiftSize.push_back(tmp_prod.size());
      }
      cout << "Total Number of Sifts: " << prod.size() << " : "
           << Img_SiftSize.size() << endl;

      vector<Product> Centroids =
          KmeansFLANN.kmeans(prod, (uint16_t)ClusterNum_K, Img_Hist, Img_SiftSize);

      writeBinaryProduct("../sifts/Final_Centroids.bin", Centroids);
      writeBinaryProduct("../sifts/Updated_Sifts.bin", prod);
      writeBinaryHistImage("../sifts/Img_Hist.bin", Img_Hist);
    } else if (3 == stoi(argv[1])) { 
      cout << "Hist_TFIDF ...." << endl;
      vector<Product> Centroids =
          readBinaryProduct("../sifts/Final_Centroids.bin"); // output of kmeans...
      cout << "Number of Final Centroids: " << Centroids.size() << " -> "
           << endl;
      vector<Product> Sifts =
          readBinaryProduct("../sifts/Updated_Sifts.bin"); // we dont use this anymore ... 
      cout << "Number of Updated Sifts: " << Sifts.size() << " -> " << endl;
      vector<HistImage> ImgHist =
          readBinaryHistImage("../sifts/Img_Hist.bin"); // hist struct of each image
      cout << "Number of histograms: " << ImgHist.size() << " -> " << endl;

      vector<vector<uint>> hist = hist_features(ImgHist, (uint)ClusterNum_K);
      vector<vector<float>> tfIdf_hist;
      uint Comp_reference = 0;
      vector<string> InpNum = getImageNames("../img"); // takeing the name of input image from /img folder
      // string input_image = "imageCompressedCam0_0000680";
      if (argc == 4) {
        // Build SIFT for Input Image
        vector<Product> prod_input;
        Mat descriptorImage_Input;
        Product tmp_input{"Empty", 0, 0, false, {0}};
        Mat descriptor_input =
            computeSifts("../img/" + InpNum[0], descriptorImage_Input);

        cout << "Input: " << InpNum[0] << endl;

        // making a product type for input image and filling in 
        for (int row = 0; row < descriptor_input.rows; row++) {
          for (int col = 0; col < descriptor_input.cols; col++) {
            tmp_input.sift[col] = descriptor_input.at<float>(row, col);
          }
          strcpy(tmp_input.name, InpNum[0].c_str());
          tmp_input.siftNum = row;
          tmp_input.isCentroid = false;
          prod_input.push_back(tmp_input);
        }

        cv::Mat centroid_Mat;
        for (size_t i = 0; i < Centroids.size(); i++) {     // Prod to Mat format ... Centriods
          cv::Mat centroid_vec(1, 128, cv::DataType<float>::type,
                               Centroids[i].sift);
          centroid_Mat.push_back(centroid_vec);
        }

        // Loop for Kmeans-Flann
        cv::flann::KDTreeIndexParams indexParams(4);
        cv::flann::Index kdtree(centroid_Mat, indexParams);
        // Store Indizes from k nearest sifts
        cv::Mat nearestVectorIdx(1, ClusterNum_K, cv::DataType<int>::type);
        cv::Mat nearestVectorDist(1, ClusterNum_K, cv::DataType<float>::type);

        for (size_t i = 0; i < prod_input.size(); i++) {    // Prod to Mat format ... Samples
          cv::Mat sift_vec(1, 128, cv::DataType<float>::type,
                           prod_input[i].sift);

          kdtree.knnSearch(sift_vec, nearestVectorIdx, nearestVectorDist, 1);

          // 1 nearest rows of prod_input get the number of cluster
          uint closestIdx = nearestVectorIdx.at<uint>(0, 0);
          prod_input[i].ClusterID = closestIdx;
          inp_Hist[0].hist[nearestVectorIdx.at<uint>(0, 0)]++;
        }
        vector<vector<uint>> inp_hist =
            hist_features(inp_Hist, (uint)ClusterNum_K);

        hist.push_back(inp_hist[0]);

        tfIdf_hist = tfIdf(hist);

        Comp_reference = tfIdf_hist.size() - 1;  
      } else if (argc == 5) {
        Comp_reference = stoi(argv[4]);
        InpNum[0] = ImageNames[stoi(argv[4])];

        cout << "Input: " << InpNum[0] << " --> data1" << endl;
        tfIdf_hist = tfIdf(hist);
      }

      vector<float> compare_hist =
          cosine_comparison(tfIdf_hist, tfIdf_hist[Comp_reference]);

      for (size_t i = 0; i < ImgHist.size(); i++) {
        // cout << i << ": " << compare_hist[i] << endl;
        // cerr << ImageNameList.size() << "  ImName --> " << ImageNameList[i].c_str() << endl;
        strcpy(ImgHist[i].name, ImageNameList[i].c_str());
        ImgHist[i].time = gps_image[i].time;
        ImgHist[i].latitude = gps_image[i].latitude;
        ImgHist[i].longitude = gps_image[i].longitude;
        ImgHist[i].CosCom = compare_hist[i];
      }
      std::sort(ImgHist.begin(), ImgHist.end(), ImgHist_sorter);

      // for (size_t i = 0; i < ImgHist.size(); i++) {
      //   cout << i << ": " << ImgHist[i].CosCom << " -> " << compare_hist[i]
      //        << endl;
      // }

      writeBinaryHistImage("../sifts/results.bin", ImgHist);
      html_print(InpNum[0], 10, argc);
    }
  } else {
    cout << "Required inputs: Mode {1:dataset_run, 2:Kmeans, 3:hist&TFIDF} , K "
            "= ? , Number of Images to read: ?"
         << endl;
  }
  return 0;
}
