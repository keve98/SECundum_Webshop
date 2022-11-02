#include <vector>
#include "../CIFF/CIFFObject.h"

using namespace std;

class CAFFAnimation {
    //BlockType.
    vector<unsigned char> ID{};
    vector<unsigned char> Length{};

    vector<unsigned char> Duration{};
    CIFFObject* CIFF{};

    int ConvertToInt(vector<unsigned char> const& toConvert);
public:
    CAFFAnimation(vector<unsigned char>::const_iterator const& animationInput);
    ~CAFFAnimation();
    int GetID();
    int GetLength();
    int GetDuration();
    CIFFObject GetCIFF();
    bool IsValid();
};