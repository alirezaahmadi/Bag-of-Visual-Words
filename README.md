# Bag of Visual Words
This is an implementation of Bag-og-visual-Words method which is able to classify images based on their similariy. The similarity here defines based on 2D photometric featues (in particular we are using SIFT features with a dimension of 128 array). The implementation is menat to be simplistic and easily be used.

it uses gps positions and timestpams to sort out the images and evaluate the results. also an HTML interface is provided wihch gets updated based on the results of each execution. inbelow you can find dependencies and more information about using code.

## Dependencies

- c++11
- cmake 2.8
- opencv 2.4 + nonfree libraies
- html

## Install OpenCV and non-free libraries

    sudo add-apt-repository --remove ppa:xqms/opencv-nonfree
    sudo add-apt-repository --yes ppa:jeff250/opencv
    sudo apt-get update
    sudo apt-get install libopencv-dev
    sudo apt-get install libopencv-nonfree-dev
    
## How to compile the code

    cd *desired directory*
    git clone https://github.com/alirezaahmadi/Bag-of-Visual-Words.git
    cd Bag-of-Visual-Words/
    mkdir build
    cd build
    cmake ..
    make 
    
Now you are ready to run the code:
## How to run code
you have 3 differnet modes to run the code
1. loading dataset and building feature space and saving them as binary files

        ./BoVW 1 *Dataset_path w.r.t to /bin folder*
    
2. loading binary files and runing K-means to classify the features based on the similarity

        ./BoVW 2
    
3. runing evaluation based on TFIDF and image histograms and finding 10 the most similar images to one test image wihch is given as input
    
        ./BoVW 3 *test image directory with .png type*
    
