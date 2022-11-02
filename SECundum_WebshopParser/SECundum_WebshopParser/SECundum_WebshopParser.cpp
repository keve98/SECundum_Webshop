// SECundum_WebshopParser.cpp : Defines the entry point for the application.
//

#include "SECundum_WebshopParser.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
            CIFFTester* tester = new CIFFTester();
            tester->WriteCIFFImage(toParse);
            delete tester;
            return 1;
        }
        else {
            cout << "The .caff file is invalid and cannot be read!" << endl;
            return 0;
        }

        delete toParse;
    }
    catch (...) {
        cout << "Something went wrong while loading the file! Parameters: 1. file to parse. Output: A .bmp image file and a .json file representing the stored data in a easy form." << endl;
        return 0;
    };
}
