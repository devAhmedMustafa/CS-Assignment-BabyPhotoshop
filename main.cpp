//Program: Baby Photoshop program
//Authors:  Malak Amr Ahmed Saleh - ID: 20230416 - S22 ---> GrayScale filter & Menu
//          Ibrahim Reda Mohamed Morsy - ID: 20230597 - S22 ---> Black and White filter & Horizontal and vertical flip filter
//          Ahmed Mustafa EL-Sheikh Talaat - ID: 20230636 - S22 ---> Invert filter & Rotate filter

//System Diagram: https://drive.google.com/file/d/16WMEV3cS-93c3tAiAGDeK93r_W2lyStY/view?usp=sharing

#include "Filters.h"
#include "Utilities.h"
using namespace std;
using namespace Filters;

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

    Image image("Raw Images/sukuna.jpg");
    AddFancyFrame(image, 20, new int[3] {156,29,26}, new int[3]{240,230,100});
    image.saveImage("framed.png");

    //Menu();
    return 0;
}

