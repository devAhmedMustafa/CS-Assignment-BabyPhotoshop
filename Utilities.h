#ifndef BABYPHOTOSHOP_UTILITIES_H
#define BABYPHOTOSHOP_UTILITIES_H

#include "Image_Class.h"

namespace Utilities{
    double StandardDeviation(Image& );
    double Mean(Image& );
    void ChangeImageData(Image& actual, Image& newImage);

    void ChangeImageData(Image& actual, Image& newImage){
        actual.width = newImage.width;
        actual.height = newImage.height;

        for (int i = 0; i < actual.width; i++){
            for (int j = 0; j < actual.height; j++){
                for (int k = 0; k < 3; k++){
                    actual.setPixel(i, j, k, newImage(i, j, k));
                }
            }
        }
    }

    double StandardDeviation(Image& image){

        double sum = 0;
        double mean = Mean(image);

        for (int i = 0; i < image.width; i++){
            for (int j = 0; j < image.height; j++) {
                float avg = 0;

                for (int k = 0; k < 3; k++){
                    avg += image(i, j, k);
                }

                avg /= 3;

                sum += pow(((float) avg - mean), 2);
            }
        }

        return sqrt(sum / ((image.width*image.height)-1));

    }

    double Mean(Image& image){

        int avg = 0;

        for (int i = 0; i < image.width; i++){
            for (int j = 0; j < image.height; j++){
                float avgC = 0;

                for (int k = 0; k < 3; k++){
                    avgC += image(i, j, k);
                }

                avgC /= 3;

                avg += avg;
            }
        }

        return avg / (image.width*image.height);
    }
}

#endif //BABYPHOTOSHOP_UTILITIES_H
