#include <cmath>
#include "Image_Class.h"

void InvertFilter(std::string filename);

void Rotate(std::string filename, int angle);

int main() {

    Rotate("yuta.jpg", 180);

    return 0;
}

void InvertFilter(std::string filename){

    Image image(filename);

    for (int i = 0; i < image.width; ++i){
        for (int j = 0; j < image.height; ++j){

            for (int k = 0; k < 3; ++k){

                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    image.saveImage("inverted.png");

}

void Rotate(std::string filename, int angle){

    Image image(filename);

    if (angle == 0)
        return;

    int shiftW, shiftH;
    bool changeDim = angle != 180;

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

    rotated.saveImage("rotated.png");

}