#include <vector>
#include <string>
#include "../CIFF/CIFFObject.h"

using namespace std;

class CAFFAnimation {
    //BlockType.
    vector<unsigned char> ID{};
    vector<unsigned char> Length{};

    vector<unsigned char> Duration{};
    CIFFObject* CIFF = nullptr;

    int ConvertToInt(vector<unsigned char> const& toConvert);
public:
    CAFFAnimation(vector<unsigned char>::const_iterator const& animationInput, int inputSize);
    ~CAFFAnimation();
    int GetID();
    int GetLength();
    int GetDuration();
    CIFFObject* GetCIFF();
    bool IsValid();
    string GetJSON(string fileName);
};