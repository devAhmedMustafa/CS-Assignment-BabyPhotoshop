#include <cmath>
#include "Image_Class.h"
using namespace std;

void InvertFilter(std::string filename);
void Rotate(std::string filename, int angle);
void grayScale_filter(Image& image);
void verticalFlip(Image& image);
void horizontalFlip(Image& image);
void Black_and_White(Image& image);

int main() {

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
                cout << "Upload your image: ";
                cin >> filename;
                Image image(filename);
                
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
                            // invert function
                            break;
                        case 5:
                            // rotate function
                            break;
                        default:
                            cout << "Invalid filter choice! Please try again.\n";
                    }
                    cout << "Do you want to apply another filter?\n"
                            "1) Yes\n"
                            "2) No\n";
                    cin >> save_choice;
                    if (save_choice == 1)
                        continue;
                    if (save_choice == 2)
                        break;
                }
                cout << "Save the image:\n"
                        "1) In the same file\n"
                        "2) In a new file\n";
                cin >> file_choice;

                if (file_choice == 1)
                    image.saveImage(filename);
                if (file_choice == 2){
                    cout << "Enter the new file name: ";
                    cin >> new_filename;
                    image.saveImage(new_filename);
                }
                break;
            }
            case 2:
                cout << "Exiting the program...Bye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 2);

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
