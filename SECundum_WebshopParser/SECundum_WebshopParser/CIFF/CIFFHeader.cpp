#include "CIFFHeader.h"

CIFFHeader::CIFFHeader(vector<unsigned char>::const_iterator const& headerInput, int inputSize) {
    //Before start check.
    if (inputSize > 36) {
        auto iterator = headerInput;

        Magic = vector<unsigned char>{ iterator, iterator + 4 };
        iterator += 4;
        inputSize -= 4;

        HeaderSize = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        ContentSize = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        Width = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        Height = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        if (inputSize + 36 - ConvertToInt(HeaderSize) >= 0) {
            for (auto i = iterator; i < iterator - 36 + ConvertToInt(HeaderSize); ++i) {
                if (*i == '\n') {
                    Caption = vector<unsigned char>{ iterator, i };
                    iterator = ++i;
                    inputSize = inputSize - Caption.size() - 1;
                    break;
                }
            }
        }

        if (inputSize + Caption.size() + 37 - ConvertToInt(HeaderSize) >= 0) {
            for (auto i = iterator; i < headerInput + ConvertToInt(HeaderSize); ++i) {
                if (*i == '\0') {
                    auto toPush = vector<unsigned char>{ iterator, i };
                    Tags.push_back(toPush);
                    iterator = ++i;
                    inputSize = inputSize - toPush.size() - 1;
                }
            }
        }
    }
}

int CIFFHeader::ConvertToInt(vector<unsigned char> const& toConvert) {
    int toReturn = 0;
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i] * pow(16, i * 2);
    }
    return toReturn;
}

string CIFFHeader::ConvertToString(vector<unsigned char> const& toConvert) {
    string toReturn = "";
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i];
    }
    return toReturn;
}

string CIFFHeader::ConvertTagsToString(vector<vector<unsigned char>> const& toConvert) {
    string toReturn = "";
    for (size_t i = 0; i < toConvert.size(); ++i) {
        auto tag = toConvert[i];
        toReturn += "\"";
        for (size_t j = 0; j < tag.size(); j++)
        {
            toReturn += tag[i] + "\"";
        }
        if (i != toConvert.size() - 1) {
            toReturn += ", ";
        }
    }
    
    return toReturn;
}

vector<unsigned char> CIFFHeader::GetMagic() {
    return Magic;
}

int CIFFHeader::GetHeaderSize() {
    return ConvertToInt(HeaderSize);
}

int CIFFHeader::GetContentSize() {
    return ConvertToInt(ContentSize);
}

int CIFFHeader::GetWidth() {
    return ConvertToInt(Width);
}

int CIFFHeader::GetHeight() {
    return ConvertToInt(Height);
}

vector<unsigned char> CIFFHeader::GetCaption() {
    return Caption;
}

vector<vector<unsigned char>> CIFFHeader::GetTags() {
    return Tags;
}

bool CIFFHeader::IsValid() {
    bool isValid = true;

    if (Magic.size() != 4 || Magic[0] != 'C' || Magic[1] != 'I' || Magic[2] != 'F' || Magic[3] != 'F') {
        isValid = false;
    }
    if (HeaderSize.size() != 8) {
        isValid = false;
    }
    if (ContentSize.size() != 8) {
        isValid = false;
    }
    if (Width.size() != 8) {
        isValid = false;
    }
    if (Height.size() != 8) {
        isValid = false;
    }
    int tagSize = Tags.size();
    for each (vector<unsigned char> tag in Tags)
    {
        tagSize += tag.size();
    }
    if (ConvertToInt(HeaderSize) !=
        Magic.size() + HeaderSize.size() + ContentSize.size() + Width.size() + Height.size() + Caption.size() + 1 + tagSize) {
        isValid = false;
    }
    if (ConvertToInt(ContentSize) != ConvertToInt(Height) * ConvertToInt(Width) * 3) {
        isValid = false;
    }

    return isValid;
}

string CIFFHeader::GetJSON() {
    return "{ \"Magic\" : \"" + ConvertToString(Magic) + "\", " +
        "\"HeaderSize\" : \"" + to_string(ConvertToInt(HeaderSize)) + "\", " +
        "\"ContentSize\" : \"" + to_string(ConvertToInt(ContentSize)) + "\", " +
        "\"Width\" : \"" + to_string(ConvertToInt(Width)) + "\", " +
        "\"Height\" : \"" + to_string(ConvertToInt(Height)) + "\", " +
        "\"Caption\" : \"" + ConvertToString(Caption) + "\", " +
        "\"Tags\" : [" + ConvertTagsToString(Tags) + "]" +
        " }";
}
