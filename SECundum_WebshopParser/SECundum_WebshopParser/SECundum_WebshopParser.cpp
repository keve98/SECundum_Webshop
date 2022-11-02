// SECundum_WebshopParser.cpp : Defines the entry point for the application.
//

#include "SECundum_WebshopParser.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace cimg_library;

void WriteCIFFImage(CIFFObject* ciff) {
    CImg<float> img(
        ciff->GetHeader().GetWidth(),
        ciff->GetHeader().GetHeight(), 1, 3);
    int row = 0;
    int col = 0;
    int num = 1;
    int red = 0;
    int green = 0;
    int blue = 0;
    auto pixels = ciff->GetContent().GetPixels();
    for (auto it = pixels.begin(); it < pixels.end() && pixels.size() > 0; it++) {
        if (num % 3 == 0) {
            blue = (int)(*it);

            //img(row, col, 1, 1) = red;
            //img(row, col, 1, 2) = green;
            //img(row, col, 1, 3) = blue;
            unsigned char color[3];
            color[0] = red;
            color[1] = green;
            color[2] = blue;
            img.draw_point(row, col, color);
            if (row + 1 == ciff->GetHeader().GetHeight() && col + 1 == ciff->GetHeader().GetWidth()) {
                break;
            }
            if (col + 1 == ciff->GetHeader().GetWidth()) {
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
    img.display();
    img.save_bmp("test.bmp");

    //TODO json
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
        CIFFObject* toParse = new CIFFObject(LoadFileFromInput("C:\\Users\\Kocsi Levente\\OneDrive\\Asztali gép\\SECundum\\6.ciff"/*argv[0]*/));

        if (toParse->IsValid()) {
            cout << "The .caff file is successfuly read!" << endl;
            WriteCIFFImage(toParse);
            return 1;
        }
        else {
            cout << "The .caff file is invalid and cannot be read!" << endl;
            return 0;
        }

        delete toParse;
    }
    catch (...) {
        cout << "Something went wrong while loading the file!" << endl;
        cout << "Parameters: 1. file to parse." << endl;
        cout << "Output: A .bmp image file and a .json file representing the stored data in a easy form." << endl;
        return 0;
    };
}
