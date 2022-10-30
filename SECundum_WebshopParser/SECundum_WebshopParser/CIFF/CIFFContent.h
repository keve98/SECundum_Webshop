#include <vector>

using namespace std;

class CIFFContent {
	vector<unsigned char> Pixels{};
public:
	CIFFContent(vector<unsigned char>::const_iterator const& contentInput, vector<unsigned char>::const_iterator const& end);
	vector<unsigned char> GetPixels();
	bool IsValid(int contentSize);
};