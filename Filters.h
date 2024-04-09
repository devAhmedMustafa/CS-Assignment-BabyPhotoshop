#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"
#include "Utilities.h"
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace Utilities;

namespace Filters {

    void InvertFilter(Image& image);
    void Rotate(Image& image, int angle);
    void grayScale_filter(Image& image);
    void verticalFlip(Image& image);
    void horizontalFlip(Image& image);
    void Black_and_White(Image& image);
    void BlurFilter(Image& image, int r);
    void AddFrame(Image& , Image& , int []);
    void Resize(Image&, int, int);
    void Noise(Image&, float power);
    void Oil(Image&,int, int);
    void Bloom(Image& , double, double);

    void Bloom(Image& image, double intensity, double threshold){

        int full = image.width*image.height;
        float current = 0;

        Image blurred(image.width, image.height);
        ChangeImageData(blurred, image);

        BlurFilter(blurred, 2);

        for (int i = 0; i < image.width; i++){
            for (int j = 0; j < image.height; j++){

                if (image(i,j,0) > threshold || image(i,j,1) > threshold || image(i,j,2) > threshold) {
                    image(i,j,0) = static_cast<unsigned char>(min(255.0, image(i,j,0) * intensity + blurred(i, j, 0)));
                    image(i,j,1) = static_cast<unsigned char>(min(255.0, image(i,j,1) * intensity + blurred(i, j, 1)));
                    image(i,j,2) = static_cast<unsigned char>(min(255.0, image(i,j,2) * intensity + blurred(i, j, 2)));
                }

                current++;
            }

            cout <<"\r" << (int)(current/full*100) << "%";
        }
    }

    void Noise(Image& image, float power){

        double mean;
        double stddev;

        mean = (Mean(image)/2)*power;
        stddev = (StandardDeviation(image)/2)*power;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> distribution(mean, stddev);

        for(int i = 0; i < image.width; i++){
            for(int j = 0; j < image.height; j++){
                for (int k = 0; k < 3; k++){
                    int noise = static_cast<int>(image(i,j,k) + distribution(gen));
                    noise = max(0, min(255, noise));
                    image(i, j, k) = noise;
                }
            }
        }
    }

    void Oil(Image& image, const int rad, int intensityLevels){

        int sumR[256] = {0};
        int sumG[256] = {0};
        int sumB[256] = {0};
        int counts[256] = {0};

        for (int i = rad; i < image.width - rad; i++){
            for (int j = rad; j < image.height - rad; j++){

                for (int x = -rad; x <= rad; x++){
                    for (int y = -rad; y <= rad; y++){

                        int r = image(i+x, j+y, 0);
                        int g = image(i+x, j+y, 1);
                        int b = image(i+x, j+y, 2);

                        int nCurIntensity = (((r+g+b)/3) * intensityLevels)/255;

                        if( nCurIntensity > 255 )
                            nCurIntensity = 255;

                        counts[nCurIntensity]++;
                        sumR[nCurIntensity] += r;
                        sumG[nCurIntensity] += g;
                        sumB[nCurIntensity] += b;
                    }
                }

                int nCurMax = 0;
                int nMaxIndex = 0;
                for (int nI = 0; nI < 256; nI++)
                {
                    if (counts[nI] > nCurMax)
                    {
                        nCurMax = counts[nI];
                        nMaxIndex = nI;
                    }
                }

                image(i, j, 0) = sumR[nMaxIndex] / nCurMax;
                image(i, j, 1) = sumG[nMaxIndex] / nCurMax;
                image(i, j, 2) = sumB[nMaxIndex] / nCurMax;

                for (int nI = 0; nI < 256; nI++)
                {
                    counts[nI] = 0;
                    sumR[nI] = 0;
                    sumG[nI] = 0;
                    sumB[nI] = 0;
                }
            }
        }
    }

    void AddFrame(Image& image, Image& frame, int color[]){

        int newWidth = image.width;
        int newHeight = image.height;

        if (newWidth <= 0 || newHeight <= 0) {
            cout << "Error: New dimensions must be positive.\n";
            return;
        }

        Image resizedImage(newWidth, newHeight);

        double widthRatio = static_cast<double>(frame.width) / newWidth;
        double heightRatio = static_cast<double>(frame.height) / newHeight;

        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int originalX = static_cast<int>(i * widthRatio);
                    int originalY = static_cast<int>(j * heightRatio);

                    resizedImage.setPixel(i, j, k, frame.getPixel(originalX, originalY, k));
                }
            }
        }

        for (int i = 0; i < image.width; i++){
            for (int j = 0; j < image.height; j++){

                int sum = 0;

                for (int k = 0; k < 3; k++){
                    sum += resizedImage(i, j, k);
                }

                if (sum >= 10){
                    for (int k = 0; k < 3; k++){
                        image(i, j, k) = color[k];
                    }
                }

            }

        }

    }

    void BlurFilter(Image& image, int r){

        int area = pow(2*r+1, 2);

        for (int i = r; i < image.width-r; i++){
            for (int j = r; j < image.height-r; j++){
                for (int k = 0; k < 3; k++){

                    int sum = 0;

                    for (int p = i-r; p <= i+r; p++){
                        for (int c = j-r; c <= j+r; c++){
                            sum += image(p, c, k);
                        }
                    }

                    image(i, j, k) = ceil(sum / area);
                }
            }
        }

    }

    void Resize(Image& originalImage, int newWidth, int newHeight) {
        if (newWidth <= 0 || newHeight <= 0) {
            cout << "Error: New dimensions must be positive.\n";
            return;
        }

        Image resizedImage(newWidth, newHeight);

        double widthRatio = static_cast<double>(originalImage.width) / newWidth;
        double heightRatio = static_cast<double>(originalImage.height) / newHeight;

        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int originalX = static_cast<int>(i * widthRatio);
                    int originalY = static_cast<int>(j * heightRatio);

                    resizedImage.setPixel(i, j, k, originalImage.getPixel(originalX, originalY, k));
                }
            }
        }

    }

    void InvertFilter(Image& image){

        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){

                for (int k = 0; k < 3; ++k){

                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }

    }

    void Rotate(Image& image, int angle){

        if (angle == 0)
            return;

        int shiftW, shiftH;
        bool changeDim = (angle != 180);

        Image rotated( changeDim?image.height:image.width, changeDim?image.width:image.height);

        if (angle == 90 || angle == 180){
            shiftW = image.width-1;
            shiftH = image.height-1;
        }else{
            shiftW = 0;
            shiftH = 0;
        }

        for (int i = 0; i < image.width; i++){
            for (int j = 0; j < image.height; j++){
                for (int k = 0; k < 3; k++){

                    int row = abs(shiftW - i);
                    int col = abs(shiftH - j);

                    rotated(changeDim?j:i, changeDim?i:j, k) = image(row, col, k);
                }
            }
        }

        ChangeImageData(image, rotated);

    }

    void grayScale_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int average = 0;
                for (int k = 0; k < 3; ++k) {
                    average += image(i,j,k);
                }
                average /= 3;
                for (int k = 0; k < 3; ++k) {
                    image(i,j,k) = average;
                }
            }
        }
    }

    void verticalFlip(Image& image) {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height / 2; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    int temp = image.getPixel(i, j, k);
                    image.setPixel(i, j, k, image.getPixel(i, image.height - 1 - j, k));
                    image.setPixel(i, image.height - 1 - j, k, temp);
                }
            }
        }
    }

    void horizontalFlip(Image& image) {
        for (int i = 0; i < image.width / 2; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    int temp = image.getPixel(i, j, k);
                    image.setPixel(i, j, k, image.getPixel(image.width - 1 - i, j, k));
                    image.setPixel(image.width - 1 - i, j, k, temp);
                }
            }
        }
    }

    void Black_and_White(Image& image){
        for(int i = 0; i < image.width; ++i)
        {
            for(int j = 0; j < image.height; ++j)
            {
                unsigned int avg = 0;
                for(int k = 0; k < 3; ++k)
                {
                    avg += image(i,j,k);
                }
                avg /= 3;

                if (avg >= 127) {
                    image.setPixel(i, j, 0, 255);
                    image.setPixel(i, j, 1, 255);
                    image.setPixel(i, j, 2, 255);
                } else {
                    image.setPixel(i, j, 0, 0);
                    image.setPixel(i, j, 1, 0);
                    image.setPixel(i, j, 2, 0);
                }
            }
        }
    }

} // Filters

#endif
