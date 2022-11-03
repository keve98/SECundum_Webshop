#include "CAFFAnimation.h"

CAFFAnimation::CAFFAnimation(vector<unsigned char>::const_iterator const& animationInput, int inputSize) {
    //Before start check.
    if (inputSize > 17) {
        auto iterator = animationInput;

        ID = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Length = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        Duration = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        CIFF = new CIFFObject(iterator, inputSize);
    }
}

CAFFAnimation::~CAFFAnimation() {
    delete CIFF;
}

int CAFFAnimation::ConvertToInt(vector<unsigned char> const& toConvert) {
    int toReturn = 0;
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i] * pow(16, i * 2);
    }
    return toReturn;
}

int CAFFAnimation::GetID() {
    return ConvertToInt(ID);
}

int CAFFAnimation::GetLength() {
    return ConvertToInt(Length);
}

int CAFFAnimation::GetDuration() {
    return ConvertToInt(Duration);
}

CIFFObject* CAFFAnimation::GetCIFF() {
    return CIFF;
}

bool CAFFAnimation::IsValid() {
    bool isValid = true;

    if (ID.size() != 1 || ConvertToInt(ID) != 3) {
        isValid = false;
    }
    if (Length.size() != 8) {
        isValid = false;
    }
    if (Duration.size() != 8) {
        isValid = false;
    }
    if (CIFF == nullptr) {
        isValid = false;
    }
    else if (!CIFF->IsValid()) {
        isValid = false;
    }

    return isValid;
}

string CAFFAnimation::GetJSON(string fileName) {
    return "{ \"ID\" : " + to_string(ConvertToInt(ID)) + ", " +
        "\"Length\" : " + to_string(ConvertToInt(Length)) + ", " +
        "\"Duration\" : " + to_string(ConvertToInt(Duration)) + ", " +
        "\"CIFF\" : " + CIFF->GetJSON(fileName) + " }";
}
