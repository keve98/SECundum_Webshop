// SECundum_WebshopParser.cpp : Defines the entry point for the application.
//

#include "SECundum_WebshopParser.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
    try {
        CIFFObject* toParse = new CIFFObject(LoadFileFromInput(argv[1]));

        if (toParse->IsValid()) {
            cout << "The .caff file is successfuly read!" << endl;
            return 1;
        }
        else {
            cout << "The .caff file is invalid and cannot be read!" << endl;
            return 0;
        }

        delete toParse;
    }
    catch (...) {
        cout << "Something went wrong while loading the file! Parameters: 1. file to parse." << endl;
        return 0;
    };
}

vector<unsigned char> LoadFileFromInput(string const& filepath)
{
    ifstream input(filepath, ios::binary);
    vector<unsigned char> buffer(istreambuf_iterator<char>(input), {});

    return buffer;
}
