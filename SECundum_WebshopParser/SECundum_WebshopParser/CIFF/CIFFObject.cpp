#include "CIFFObject.h"

CIFFObject::CIFFObject(vector<unsigned char> const& input) {
    Header = new CIFFHeader(input);

    auto iterator = input.begin();
    iterator += Header->GetHeaderSize();

    Content = new CIFFContent(iterator, input.end());
}

CIFFObject::~CIFFObject() {
    delete Header;
    delete Content;
}

CIFFHeader CIFFObject::GetHeader() {
    return *Header;
}

CIFFContent CIFFObject::GetContent() {
    return *Content;
}

bool CIFFObject::IsValid() {
    return (*Header).IsValid() && (*Content).IsValid((*Header).GetContentSize());
}
