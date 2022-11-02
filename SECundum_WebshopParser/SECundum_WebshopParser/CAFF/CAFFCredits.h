#include <vector>

using namespace std;

class CAFFCredits {
    //BlockType.
    vector<unsigned char> ID{};
    vector<unsigned char> Length{};

    vector<unsigned char> Year{};
    vector<unsigned char> Month{};
    vector<unsigned char> Day{};
    vector<unsigned char> Hour{};
    vector<unsigned char> Minute{};
    vector<unsigned char> CreatorLen{};
    vector<unsigned char> Creator{};

    int ConvertToInt(vector<unsigned char> const& toConvert);
public:
    CAFFCredits(vector<unsigned char>::const_iterator const& creditsInput);
    int GetID();
    int GetLength();
    int GetYear();
    int GetMonth();
    int GetDay();
    int GetHour();
    int GetMinute();
    int GetCreatorLen();
    vector<unsigned char> GetCreator();
    bool IsValid();
};