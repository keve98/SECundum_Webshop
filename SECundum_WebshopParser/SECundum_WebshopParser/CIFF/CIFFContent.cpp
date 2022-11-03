#include "CIFFContent.h"

CIFFContent::CIFFContent(vector<unsigned char>::const_iterator const& contentInput, vector<unsigned char>::const_iterator const& end, int width, int height) {
    Width = width;
    Height = height;
    Pixels = vector<unsigned char>{ contentInput, end };
}

vector<unsigned char> CIFFContent::GetPixels() {
    return Pixels;
}

bool CIFFContent::IsValid() {
    return (int)Pixels.size() == Height * Width * 3;
}

string CIFFContent::GetJSON(string fileName) {
    return "{ \"ImageFileName\" : \"" + fileName + "\" }";
}
