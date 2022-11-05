// SECundum_WebshopParser.cpp : Defines the entry point for the application.
//

#include "SECundum_WebshopParser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace cimg_library;

void WriteCAFFTToJSONandBMP(string title, CAFFObject* caff) {
    for (size_t i = 0; i < caff->GetHeader().GetNumAnim(); i++)
    {
        int width = caff->GetAnimationAt(i)->GetCIFF()->GetHeader().GetWidth();
        int height = caff->GetAnimationAt(i)->GetCIFF()->GetHeader().GetHeight();
        CImg<float> img(width, height, 1, 3);

        int row = 0;
        int col = 0;
        int num = 1;
        int red = 0;
        int green = 0;
        int blue = 0;

        auto pixels = caff->GetAnimationAt(i)->GetCIFF()->GetContent().GetPixels();
        for (auto it = pixels.begin(); it < pixels.end() && pixels.size() > 0; it++) {
            if (num % 3 == 0) {
                blue = (int)(*it);

                unsigned char color[3];
                color[0] = red;
                color[1] = green;
                color[2] = blue;

                img.draw_point(col, row, color);

                if (row + 1 == height && col + 1 == width) {
                    break;
                }
                if (col + 1 == width) {
                    ++row;
                    col = 0;
                }
                else {
                    ++col;
                }
            }
            else if (num % 3 == 1) {
                red = (int)(*it);
            }
            else {
                green = (int)(*it);
            }
            ++num;
        }

        //For testing: img.display();
        string toSave = title + "_" + to_string(i) + ".bmp";
        img.save_bmp(toSave.c_str());
    }

    ofstream file;
    file.open(title + ".json");
    file << "{ \"Data\" : " + caff->GetJSON(title) + " }";
    file.close();
}

vector<unsigned char> LoadFileFromInput(string const& filepath)
{
    ifstream input(filepath, ios::binary);
    vector<unsigned char> buffer(istreambuf_iterator<char>(input), {});

    return buffer;
}

int main(int argc, const char* argv[])
{
    try {
        if (argc > 1) {
            //For testing: "C:\\Users\\Kocsi Levente\\OneDrive\\Asztali gép\\SECundum\\1.caff"
            //For testing: "C:\\Users\\Kocsi Levente\\OneDrive\\Asztali gép\\SECundum\\1_bad.caff"
            CAFFObject* toParse = new CAFFObject(LoadFileFromInput(argv[1]));

            if (toParse->IsValid()) {
                cout << "The .caff file is successfuly read!" << endl;
                WriteCAFFTToJSONandBMP("myCaff", toParse);
                return 1;
            }
            else {
                cout << "The .caff file is invalid and cannot be read!" << endl;
                return 0;
            }

            delete toParse;
        }
        else {
            cout << "Please call the application with parameters!" << endl;
            cout << "Parameters: 1. file to parse." << endl;
            cout << "Output: A .bmp image file and a .json file representing the stored data in a easy form." << endl;
        }
    }
    catch (...) {
        cout << "Something went wrong while loading the file!" << endl;
        cout << "Parameters: 1. file to parse." << endl;
        cout << "Output: A .bmp image file and a .json file representing the stored data in a easy form." << endl;
        return 0;
    };
}
