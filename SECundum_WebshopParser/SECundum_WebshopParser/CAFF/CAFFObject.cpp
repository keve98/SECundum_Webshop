#include "CAFFObject.h"

CAFFObject::CAFFObject(vector<unsigned char> const& input) {
    Header = new CAFFHeader(input);

    auto iterator = input.begin();
    iterator = iterator + 9 + Header->GetLength();

    Credits = new CAFFCredits(iterator);

    iterator = iterator + 9 + Credits->GetLength();

    Animations = vector<CAFFAnimation*>{};
    for (size_t i = 0; i < Header->GetNumAnim(); i++)
    {
        CAFFAnimation* anim = new CAFFAnimation(iterator);
        iterator = iterator + 17 + anim->GetCIFF()->GetHeader().GetHeaderSize() + anim->GetCIFF()->GetHeader().GetContentSize();
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

    if (!(*Header).IsValid() || !(*Credits).IsValid()) {
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

    for each (CAFFAnimation* anim in Animations)
    {
        animations += anim->GetJSON(fileName) + ", ";
    }

    return "{ \"Header\" : " + Header->GetJSON() + ", " +
        " \"Credits\" : " + Credits->GetJSON() + "," +
        " \"Animations\" : [" + animations + "] }";
}
