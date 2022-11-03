#include <vector>
#include <string>

using namespace std;

class CIFFHeader {
    vector<unsigned char> Magic{};
    vector<unsigned char> HeaderSize{};
    vector<unsigned char> ContentSize{};
    vector<unsigned char> Width{};
    vector<unsigned char> Height{};
    vector<unsigned char> Caption{};
    vector<vector<unsigned char>> Tags{};

    int ConvertToInt(vector<unsigned char> const& toConvert);
    string ConvertToString(vector<unsigned char> const& toConvert);
    string ConvertTagsToString(vector<vector<unsigned char>> const& toConvert);
public:
    CIFFHeader(vector<unsigned char>::const_iterator const& headerInput, int inputSize);
    vector<unsigned char> GetMagic();
    int GetHeaderSize();
    int GetContentSize();
    int GetWidth();
    int GetHeight();
    vector<unsigned char> GetCaption();
    vector<vector<unsigned char>> GetTags();
    bool IsValid();
    string GetJSON();
};
