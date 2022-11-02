#include "CAFFAnimation.h"

CAFFAnimation::CAFFAnimation(vector<unsigned char>::const_iterator const& animationInput) {
    auto iterator = animationInput;

    ID = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Length = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    Duration = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    CIFF = new CIFFObject(iterator);
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
    //TODO
    return true;
}
