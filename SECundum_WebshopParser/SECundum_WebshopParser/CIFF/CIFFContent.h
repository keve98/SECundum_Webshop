#include <vector>
#include <string>

using namespace std;

class CIFFContent {
	int Width;
	int Height;
	vector<unsigned char> Pixels{};
public:
	CIFFContent(vector<unsigned char>::const_iterator const& contentInput, vector<unsigned char>::const_iterator const& end, int width, int height);
	vector<unsigned char> GetPixels();
	bool IsValid();
	string GetJSON(string fileName);
};