#include <vector>
#include <string>
#include "CIFFHeader.h"
#include "CIFFContent.h"

using namespace std;

class CIFFObject {
    CIFFHeader* Header = nullptr;
    CIFFContent* Content = nullptr;
public:
    CIFFObject(vector<unsigned char>::const_iterator const& input, int inputSize);
    ~CIFFObject();
    CIFFHeader GetHeader();
    CIFFContent GetContent();
    bool IsValid();
    string GetJSON(string fileName);
};
