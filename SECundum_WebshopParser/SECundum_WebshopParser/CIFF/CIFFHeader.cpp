#include "CIFFHeader.h"

CIFFHeader::CIFFHeader(vector<unsigned char> const& headerInput) {
    auto iterator = headerInput.begin();

    Magic = vector<unsigned char>{ iterator, iterator + 4 };
    iterator += 4;

    HeaderSize = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    ContentSize = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    Width = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    Height = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    for (auto i = iterator; i < iterator - 36 + ConvertToInt(HeaderSize); ++i) {
        if (*i == '\n') {
            Caption = vector<unsigned char>{ iterator, i };
            iterator = ++i;
            break;
        }
    }

    for (auto i = iterator; i < headerInput.begin() + ConvertToInt(HeaderSize); ++i) {
        if (*i == '\0') {
            Tags.push_back(&(*iterator));
            iterator = ++i;
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

vector<const unsigned char*> CIFFHeader::GetTags() {
    return Tags;
}

bool CIFFHeader::IsValid() {
    bool isValid = true;

    if (Magic[0] != 'C' || Magic[1] != 'I' || Magic[2] != 'F' || Magic[3] != 'F') {
        isValid = false;
    }

    /*
    if (HeaderSize.size() != 8 ||
        ConvertToInt(HeaderSize) !=
        Magic.size() + HeaderSize.size() + ContentSize.size() + Width.size() + Height.size() + Caption.size() + Tags.size()) {
        isValid = false;
    }
    */

    if (ConvertToInt(ContentSize) != ConvertToInt(Height) * ConvertToInt(Width) * 3) {
        isValid = false;
    }

    return isValid;
}
