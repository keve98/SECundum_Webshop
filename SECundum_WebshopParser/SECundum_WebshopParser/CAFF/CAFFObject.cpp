#include "CAFFObject.h"

CAFFObject::CAFFObject(vector<unsigned char> const& input) {
    int inputSize = input.size();
    auto iterator = input.begin();
    
    Header = new CAFFHeader(input, inputSize);

    iterator = iterator + 9 + Header->GetLength();
    inputSize = inputSize - 9 - Header->GetLength();

    Credits = new CAFFCredits(iterator, inputSize);

    iterator = iterator + 9 + Credits->GetLength();
    inputSize = inputSize - 9 - Credits->GetLength();

    Animations = vector<CAFFAnimation*>{};
    for (size_t i = 0; i < Header->GetNumAnim(); i++)
    {
        CAFFAnimation* anim = new CAFFAnimation(iterator, inputSize);

        if (inputSize - 17 - anim->GetCIFF()->GetHeader().GetHeaderSize() - anim->GetCIFF()->GetHeader().GetContentSize() >= 0) {
            iterator = iterator + 17 + anim->GetCIFF()->GetHeader().GetHeaderSize() + anim->GetCIFF()->GetHeader().GetContentSize();
            inputSize = inputSize - 17 - anim->GetCIFF()->GetHeader().GetHeaderSize() - anim->GetCIFF()->GetHeader().GetContentSize();
        }
        else {
            break;
        }

        Animations.push_back(anim);
    }
}

CAFFObject::~CAFFObject() {
    delete Header;
    delete Credits;
    for each (CAFFAnimation * anim in Animations)
    {
        delete anim;
    }
}

CAFFHeader CAFFObject::GetHeader() {
    return *Header;
}

CAFFCredits CAFFObject::GetCredits() {
    return *Credits;
}

CAFFAnimation* CAFFObject::GetAnimationAt(int idx) {
    return Animations.at(idx);
}

bool CAFFObject::IsValid() {
    bool isValid = true;

    if (!Header->IsValid() || !Credits->IsValid()) {
        isValid = false;
    }
    if (Header->GetNumAnim() != Animations.size()) {
        isValid = false;
    }
    for each (CAFFAnimation* anim in Animations)
    {
        if (!anim->IsValid()) {
            isValid = false;
        }
    }

    return isValid;
}

string CAFFObject::GetJSON(string fileName) {
    string animations = "";

    for (size_t i = 0; i < Animations.size(); i++)
    {
        animations += Animations[i]->GetJSON("" + fileName + "_" + to_string(i) + ".bmp");
        if (i != Animations.size() - 1) {
            animations += ", ";
        }
    }

    return "{ \"Header\" : " + Header->GetJSON() + ", " +
        " \"Credits\" : " + Credits->GetJSON() + "," +
        " \"Animations\" : [" + animations + "] }";
}
