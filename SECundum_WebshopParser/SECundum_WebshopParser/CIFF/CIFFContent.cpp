#include "CIFFContent.h"

CIFFContent::CIFFContent(vector<unsigned char>::const_iterator const& contentInput, vector<unsigned char>::const_iterator const& end) {
    Pixels = vector<unsigned char>{ contentInput, end };
}

vector<unsigned char> CIFFContent::GetPixels() {
    return Pixels;
}

bool CIFFContent::IsValid(int contentSize) {
    return Pixels.size() == contentSize;
}
