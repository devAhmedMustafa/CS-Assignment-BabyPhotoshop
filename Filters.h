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
    void AddBorder(Image&, int , int , int , int, const int[]);
    void DrawMatrix(Image&, int**, int, int, int, const int [], int, int);
    void DrawFancyFrame(Image&, int**, int, int, const int[], int, int);
    void AddBasicFrame(Image&, int , const int [], int , int);
    void AddLinedFrame(Image&, int, const int[], const int[]);
    void AddFancyFrame(Image&, int, const int[], const int[]);

    void AddBorder(Image& image, int xo, int xf, int yo, int yf, const int color[]){
        if (xo > xf)
            std::swap(xo, xf);
        if(yo > yf)
            std::swap(yo, yf);

        for (int i = xo; i < xf; i++){
            for (int j = yo; j < yf; j++){
                for (int k = 0; k < 3; k++){
                    image(i, j, k) = color[k];
                }
            }
        }
    }
    void AddBasicFrame(Image& image, int thickness, const int color[], int xo = 0, int yo = 0){
        AddBorder(image, xo, image.width-xo, yo, thickness+yo, color);
        AddBorder(image, xo, image.width-xo, image.height-1-yo, image.height-thickness-yo, color);
        AddBorder(image, xo, thickness+xo, yo, image.height-yo, color);
        AddBorder(image, image.width-1-xo, image.width-thickness-xo, yo, image.height-yo, color);
    }
    void AddLinedFrame(Image& image, int thickness, const int color[], const int minorColor[]){
        AddBasicFrame(image, thickness, color);

        int whiteOutlineThickness = thickness / 6;

        AddBasicFrame(image, whiteOutlineThickness, minorColor, thickness, thickness);
        AddBasicFrame(image, whiteOutlineThickness, minorColor, thickness*1.5, thickness*1.5);

    }
    void DrawMatrix(Image& image, int** matrix, int rows, int cols, int thickness, const int color[], int xo = 0, int yo = 0){

        int dx = 1, dy = 1;
        if (xo > image.width/2)
            dx = -1;
        if (yo > image.height/2)
            dy = -1;

        for (int i = 0; abs(i) < rows*thickness; i++){
            for (int j = 0; abs(j) < cols*thickness; j++){

                if (!matrix[(int)(j/thickness)][(int)(i/thickness)])
                    continue;

                for (int k = 0; k < 3; k++){
                    image(dx*i+xo, dy*j+yo, k) = color[k];
                }

            }

        }
    }
    void DrawFancyFrame(Image& image, int** matrix, int rows, int cols, int thickness, const int color[], int xo = 0, int yo = 0){
        DrawMatrix(image, matrix, rows, cols, thickness, color, xo, yo);
        DrawMatrix(image, matrix, rows, cols, thickness, color, image.width-1-xo, yo);
        DrawMatrix(image, matrix, rows, cols, thickness, color, xo, image.height-1-yo);
        DrawMatrix(image, matrix, rows, cols, thickness, color, image.width-1-xo, image.height-1-yo);
    }
    void AddFancyFrame(Image& image, int thickness, const int color[], const int minorColor[]){
        AddBasicFrame(image, thickness, color);
        AddBasicFrame(image, thickness/6, minorColor, thickness*1.5, thickness*1.5);
        AddBasicFrame(image, thickness/8, minorColor, thickness/2, thickness/2);

        int** square = new int*[2];
        square[0] = new int[] {1,1};
        square[1] = new int[] {1,1};

        int** hollowSquare = new int*[4];
        hollowSquare[0] = new int[] {0,0,0,1};
        hollowSquare[1] = new int[] {0,0,0,1};
        hollowSquare[2] = new int[] {0,0,0,1};
        hollowSquare[3] = new int[] {1,1,1,1};

        int** circle = new int*[11];
        for (int i = 0; i < 11; i++){
            circle[i] = new int[11] {0};
        }
        MakeCircle(circle, 5);

        int filledSquareThickness = thickness/4;
        int hollowSquareThickness = thickness/2;
        int circleThickness = thickness/10;

        DrawFancyFrame(image, square, 2, 2, filledSquareThickness, minorColor, thickness, thickness);
        DrawFancyFrame(image, hollowSquare, 4, 4, hollowSquareThickness, minorColor, thickness, thickness);
        DrawFancyFrame(image, hollowSquare, 4, 4, hollowSquareThickness/2, minorColor, thickness, thickness);
        DrawFancyFrame(image, circle, 11, 11, circleThickness, minorColor, thickness*1.5+1, hollowSquareThickness*4+thickness);
        DrawFancyFrame(image, circle, 11, 11, circleThickness, minorColor, hollowSquareThickness*4+thickness, thickness*1.5+1);

    }

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

    void Resize(Image& originalImage, int newWidth, int newHeight){
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

        ChangeImageData(originalImage, resizedImage);
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

    void brighten_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i,j,k) = min(image(i,j,k)*1.5,255.0);

                }
            }
        }
    }

    void darken_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i,j,k) *= 0.5;
                }
            }
        }
    }

    void merge_filter(Image& image1, Image& image2){
        int width1 = image1.width , height1 = image1.height;
        int width2 = image2.width , height2 = image2.height;

        if (width1 == width2 && height1 != height2){
            height1 = min(height1,height2);
        }
        if (width1 != width2 && height1 == height2){
            width1 = min(width1,width2);
        }
        if (width1 != width2 && height1 != height2){
            width1 = min(width1,width2);
            height1 = min(height1,height2);
        }

        image1.width = width1;
        image1.height = height1;

        for (int i = 0; i < image1.width; ++i) {
            for (int j = 0; j < image1.height; ++j) {
                for (int k = 0; k < 3; ++k) {

                    image1(i,j,k) = (image1(i,j,k)+image2(i,j,k))/2;
                }
            }
        }
    }

    void sunlight_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i,j,k) = min(image(i,j,k)*0.95,255.0);
                }
                image(i, j, 0) = min(image(i, j, 0) + 55.0, 255.0);
                image(i, j, 1) = min(image(i, j, 1) + 50.0, 255.0);
            }
        }
    }

    void cropImage(Image& originalImage, int x, int y, int width, int height) {
        if (x < 0 || y < 0 || x + width > originalImage.width || y + height > originalImage.height) {
            cout << "Error: Cropping dimensions exceed image boundaries.\n";
            return;
        }

        Image croppedImage(width, height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    croppedImage.setPixel(i, j, k, originalImage.getPixel(x + i, y + j, k));
                }
            }
        }

        ChangeImageData(originalImage, croppedImage);
    }

    void detect_edge(Image& image) {
        int horizontal[3][3] = {{-1, 0,1},
                                {-2, 0, 2},
                                {-1, 0, 1}};

        int vertical[3][3] = {{-1, -2, -1},
                              {0, 0,0},
                              {1, 2, 1}} ;

        Image gradient(image.width, image.height);

        for (int i = 1; i < image.width -1; ++i) {
            for (int j = 1; j < image.height; ++j) {
                int horizontal_gradient[3] = {0, 0, 0};
                for (int di = -1; di <= 1 ; ++di) {
                    for (int dj = -1; dj <= 1 ; ++dj) {
                        for (int k = 0; k < 3; ++k) {
                            horizontal_gradient[k] += image(i + di, j + dj, k) * horizontal[di+1][dj+1];
                        }
                    }
                }

                int vertical_gradient[3] = {0, 0, 0};
                for (int di = -1; di <= 1 ; ++di) {
                    for (int dj = -1; dj <= 1 ; ++dj) {
                        for (int k = 0; k < 3; ++k) {
                            vertical_gradient[k] += image(i + di, j + dj, k) * vertical[di+1][dj+1];
                        }
                    }
                }

                int gradientMagnitude = 0;
                for (int k = 0; k < 3; ++k) {
                    gradientMagnitude += horizontal_gradient[k] * horizontal_gradient[k] + vertical_gradient[k] * vertical_gradient[k];
                }

                gradientMagnitude = sqrt(gradientMagnitude)/3;

                for (int k = 0; k < 3; ++k) {
                    gradient(i, j, k) = gradientMagnitude;
                }
            }
        }

        int threshold = 100;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if(gradient(i,j,0)> threshold){
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) = 0;
                    }
                }else {
                    for (int k = 0; k < 3; ++k) {
                        image(i,j,k)= 255;
                    }
                }
            }
        }
    }

    void infrared_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                image(i, j, 0) = min(image(i, j, 0) * 55.0, 255.0);

                image(i, j, 2) = 255 - image(i, j, 2);
                image(i, j, 1) = 255 - image(i, j, 1);

            }
        }
    }

    void GammaFilter(Image& image, double gamma) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    double color = image(i, j, k) / 255.0;
                    color = pow(color, gamma);
                    image(i, j, k) = static_cast<int>(color * 255);
                }
            }
        }
    }

    void purple_filter(Image& image){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                image(i, j, 0) = min(image(i, j, 0) * 1.141, 255.0);
                image(i, j, 2) = min(image(i, j, 2) * 1.26, 255.0);
                image(i, j, 1) = min(image(i, j, 1) * 0.805, 255.0);
            }
        }
    }

} // Filters

#endif
