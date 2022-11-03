#include "CAFFHeader.h"

CAFFHeader::CAFFHeader(vector<unsigned char> const& headerInput, int inputSize) {
    auto iterator = headerInput.begin();

    //Before start check.
    if (inputSize > 29) {
        ID = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Length = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        Magic = vector<unsigned char>{ iterator, iterator + 4 };
        iterator += 4;
        inputSize -= 4;

        HeaderSize = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        NumAnim = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;
    }
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

    if (ID.size() != 1 || ConvertToInt(ID) != 1) {
        isValid = false;
    }
    if (Length.size() != 8) {
        isValid = false;
    }
    if (Magic.size() != 4 || Magic[0] != 'C' || Magic[1] != 'A' || Magic[2] != 'F' || Magic[3] != 'F') {
        isValid = false;
    }
    if (HeaderSize.size() != 8) {
        isValid = false;
    }
    else if (ConvertToInt(HeaderSize) != Magic.size() + HeaderSize.size() + NumAnim.size()) {
        isValid = false;
    }
    if (NumAnim.size() != 8) {
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
