//Program: Baby Photoshop program
//Authors:  Malak Amr Ahmed Saleh - ID: 20230416 - S22 ---> GrayScale filter & Menu
//          Ibrahim Reda Mohamed Morsy - ID: 20230597 - S22 ---> Black and White filter & Horizontal and vertical flip filter
//          Ahmed Mustafa EL-Sheikh Talaat - ID: 20230636 - S22 ---> Invert filter & Rotate filter

//System Diagram: https://drive.google.com/file/d/16WMEV3cS-93c3tAiAGDeK93r_W2lyStY/view?usp=sharing


#include <cmath>
#include "Utilities.h"
#include "Image_Class.h"
#include <vector>
using namespace std;

void InvertFilter(Image& image);
void Rotate(Image& image, int angle);
void grayScale_filter(Image& image);
void verticalFlip(Image& image);
void horizontalFlip(Image& image);
void Black_and_White(Image& image);
void ChangeImageData(Image& actual, Image& newImage);
void BlurFilter(Image& image, int r);
void AddFrame(Image& image);
void Resize(Image&, int, int);

void Menu(){
    cout << "Welcome to our baby photoshop program!\n";
    int choice, filter_choice, flip_choice, save_choice, file_choice;
    string new_filename;
    do {
        cout << "What do you want to do?\n"
             << "1) Edit an image\n"
             << "2) Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string filename;

                Image image;

                // Upload Image
                while(true){
                    try{
                        cout << "Upload your image: ";
                        cin >> filename;

                        image.loadNewImage(filename);
                        break;
                    }
                    catch (...) {

                    }
                }
                // End Upload

                // Choose Filters
                while (true) {
                    cout << "Choose the filter you want to apply:\n"
                            "1) Gray Scale filter\n"
                            "2) Black and White filter\n"
                            "3) Flip filter\n"
                            "4) Invert filter\n"
                            "5) Rotate filter\n"
                            "Enter your choice: ";
                    cin >> filter_choice;

                    switch (filter_choice) {
                        case 1:
                            grayScale_filter(image);
                            break;
                        case 2:
                            Black_and_White(image);
                            break;
                        case 3:
                            cout << "1) Horizontal flip\n"
                                 << "2) Vertical flip\n"
                                 << "Enter your choice: ";
                            cin >> flip_choice;
                            switch (flip_choice) {
                                case 1:
                                    horizontalFlip(image);
                                    break;
                                case 2:
                                    verticalFlip(image);
                                    break;
                            }
                            break;
                        case 4:
                            InvertFilter(image);
                            break;
                        case 5:
                            while(true){
                                cout << "Enter Rotate Angle: " << endl;
                                cout << "1) 90 deg" << endl;
                                cout << "2) 180 deg" << endl;
                                cout << "3) 270 deg" << endl;

                                int choice;
                                int angle = 0;
                                cin >> choice;

                                if (choice == 1)
                                    angle = 90;
                                else if (choice == 2)
                                    angle = 180;
                                else if (choice == 3)
                                    angle = 270;
                                else{
                                    cout << "Invalid Choice!" << endl;
                                    continue;
                                }

                                Rotate(image, angle);
                                break;
                            }
                            break;
                        default:
                            cout << "Invalid filter choice! Please try again.\n";
                            continue;
                    }

                    // Filters Combinations
                    while (true){
                        cout << "Do you want to apply another filter?\n"
                                "1) Yes!\n"
                                "2) No, save the file\n";
                        cin >> save_choice;

                        if (save_choice != 1 && save_choice != 2){
                            cout << "Invalid Choice!" << endl;
                            continue;
                        }
                        break;
                    }


                    if (save_choice == 1)
                        continue;
                    if (save_choice == 2)
                        break;

                }
                // End Choose Filters

                // Saving Options
                while (true){
                    cout << "Save the image:\n"
                            "1) In the same file\n"
                            "2) In a new file\n";
                    cin >> file_choice;
                    switch (file_choice) {
                        case 1:
                            image.saveImage(filename);
                            break;
                        case 2:

                            while(true){

                                try{
                                    cout << "Enter the new file name and write its extension (.jpg | .bmp | .jpeg | .png): ";
                                    cin >> new_filename;
                                    image.saveImage(new_filename);
                                    break;
                                }
                                catch (...) {}
                            }

                            break;
                        default:
                            cout << "Invalid choice!\n";
                            continue;
                    }
                    break;
                }
                // End Saving Options

                break;
            }
            case 2:
                cout << "Exiting the program...Bye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 2);
}

int main() {

    Image image("sk.png");

    AddFrame(image);

    //Menu();
    return 0;
}

void AddFrame(Image& image){

    int blueColor[] = {0, 0, 200};

    Image frame("Frames Patterns/1.png");

    if (frame.width > image.width){

    }

    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){

            for (int k = 0; k < 3; k++){



            }

        }

    }

    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){

            for (int k = 0; k < 3; k++){

                image(i, j, k) = blueColor[k];

            }

        }

    }

}

void Resize(Image& image, int x, int y){

    float xFactor = round( (float) image.width / (float) x);
    float yFactor = round( (float) image.height / (float) y);

    Image resized(x, y);

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