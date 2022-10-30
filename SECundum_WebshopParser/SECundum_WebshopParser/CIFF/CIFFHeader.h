#include <vector>

using namespace std;

class CIFFHeader {
    vector<unsigned char> Magic{};
    vector<unsigned char> HeaderSize;
    vector<unsigned char> ContentSize;
    vector<unsigned char> Width;
    vector<unsigned char> Height;
    vector<unsigned char> Caption{};
    vector<const unsigned char*> Tags{};

    int ConvertToInt(vector<unsigned char> const& toConvert);
public:
    CIFFHeader(vector<unsigned char> const& headerInput);
    vector<unsigned char> GetMagic();
    int GetHeaderSize();
    int GetContentSize();
    int GetWidth();
    int GetHeight();
    vector<unsigned char> GetCaption();
    vector<const unsigned char*> GetTags();
    bool IsValid();
};
