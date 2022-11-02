#include "CAFFHeader.h"

CAFFHeader::CAFFHeader(vector<unsigned char> const& headerInput) {
    auto iterator = headerInput.begin();

    ID = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Length = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    Magic = vector<unsigned char>{ iterator, iterator + 4 };
    iterator += 4;

    HeaderSize = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    NumAnim = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;
}

int CAFFHeader::ConvertToInt(vector<unsigned char> const& toConvert) {
    int toReturn = 0;
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i] * pow(16, i * 2);
    }
    return toReturn;
}

string CAFFHeader::ConvertToString(vector<unsigned char> const& toConvert) {
    string toReturn = "";
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i];
    }
    return toReturn;
}

int CAFFHeader::GetID() {
    return ConvertToInt(ID);
}

int CAFFHeader::GetLength() {
    return ConvertToInt(Length);
}

vector<unsigned char> CAFFHeader::GetMagic() {
    return Magic;
}

int CAFFHeader::GetHeaderSize() {
    return ConvertToInt(HeaderSize);
}

int CAFFHeader::GetNumAnim() {
    return ConvertToInt(NumAnim);
}

bool CAFFHeader::IsValid() {
    bool isValid = true;

    if (Magic[0] != 'C' || Magic[1] != 'A' || Magic[2] != 'F' || Magic[3] != 'F') {
        isValid = false;
    }

    return isValid;
}

string CAFFHeader::GetJSON() {
    return "{ \"ID\" : " + to_string(ConvertToInt(ID)) + ", " +
        "\"Length\" : " + to_string(ConvertToInt(Length)) + ", " +
        "\"Magic\" : \"" + ConvertToString(Magic) + "\", " +
        "\"HeaderSize\" : " + to_string(ConvertToInt(HeaderSize)) + ", " +
        "\"NumAnim\" : " + to_string(ConvertToInt(NumAnim)) + " }";
}
