#include <vector>
#include "CAFFHeader.h"
#include "CAFFCredits.h"
#include "CAFFAnimation.h"

using namespace std;

class CAFFObject {
    CAFFHeader* Header;
    CAFFCredits* Credits;
    vector<CAFFAnimation*> Animations{};
public:
    CAFFObject(vector<unsigned char> const& input);
    ~CAFFObject();
    CAFFHeader GetHeader();
    CAFFCredits GetCredits();
    CAFFAnimation GetAnimationAt(int idx);
    bool IsValid();
};
