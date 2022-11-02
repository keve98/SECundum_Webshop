#include "CAFFObject.h"

CAFFObject::CAFFObject(vector<unsigned char> const& input) {
    Header = new CAFFHeader(input);

    auto iterator = input.begin();
    iterator += Header->GetLength();

    Credits = new CAFFCredits(iterator);

    iterator += Credits->GetLength();

    Animations = vector<CAFFAnimation*>{};
    //TODO
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

CAFFAnimation CAFFObject::GetAnimationAt(int idx) {
    return *Animations.at(idx);
}

bool CAFFObject::IsValid() {
    bool isValid = true;

    if (!(*Header).IsValid() || !(*Credits).IsValid()) {
        isValid = false;
    }
    for each (CAFFAnimation* anim in Animations)
    {
        //if (!anim->IsValid()) {
        //    isValid = false;
        //}
    }

    return isValid;
}
