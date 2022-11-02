#include <vector>
#include <string>

using namespace std;

class CAFFHeader {
    //BlockType.
    vector<unsigned char> ID{};
    vector<unsigned char> Length{};

    vector<unsigned char> Magic{};
    vector<unsigned char> HeaderSize{};
    vector<unsigned char> NumAnim{};

    int ConvertToInt(vector<unsigned char> const& toConvert);
    string ConvertToString(vector<unsigned char> const& toConvert);
public:
    CAFFHeader(vector<unsigned char> const& headerInput);
    int GetID();
    int GetLength();
    vector<unsigned char> GetMagic();
    int GetHeaderSize();
    int GetNumAnim();
    bool IsValid();
    string GetJSON();
};