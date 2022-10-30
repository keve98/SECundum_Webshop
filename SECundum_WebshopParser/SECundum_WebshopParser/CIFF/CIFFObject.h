#include <vector>
#include "CIFFHeader.h"
#include "CIFFContent.h"

using namespace std;

class CIFFObject {
    CIFFHeader* Header;
    CIFFContent* Content;
public:
    CIFFObject(vector<unsigned char> const& input);
    ~CIFFObject();
    CIFFHeader GetHeader();
    CIFFContent GetContent();
    bool IsValid();
};
