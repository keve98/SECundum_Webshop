#include "CIFFTester.h"
#include <iostream>
#include <fstream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

void CIFFTester::WriteCIFFImage(CIFFObject* ciff) {
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
    
    /*
    char* title = new char[ciff->GetHeader().GetCaption().size() + 1 + 4];

    auto iterator = ciff->GetHeader().GetCaption();
    int i;
    for (i = 0; iterator.begin() + i < iterator.end(); ++i) {
        title[i] = ciff->GetHeader().GetCaption().at(i);
    }
    title[i] = '\0';
    const char dat[5] = ".dat";

    strncat(title, dat, 4);

    cout << title << endl;

    ofstream wf;
    wf.open(title, ios::out | ios::binary);
    wf << ciff->GetHeader().GetWidth() << endl;
    wf << ciff->GetHeader().GetHeight() << endl;

    auto pixels = ciff->GetContent().GetPixels();
    for (auto it = pixels.begin(); it < pixels.end() && pixels.size() > 0; it++) {
        wf << (*it);
    }
    
    wf.close();
    delete[] title;
    */
}