#include "CIFFObject.h"

CIFFObject::CIFFObject(vector<unsigned char>::const_iterator const& input, int inputSize) {
    Header = new CIFFHeader(input, inputSize);
    
    auto iterator = input;
    iterator += Header->GetHeaderSize();
    inputSize -= Header->GetHeaderSize();

    if (inputSize >= Header->GetContentSize()) {
        Content = new CIFFContent(iterator, iterator + Header->GetContentSize(), Header->GetWidth(), Header->GetHeight());
    }
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
    return Header->IsValid() && Content->IsValid();
}

string CIFFObject::GetJSON(string fileName) {
    return "{ \"Header\" : " + Header->GetJSON() +  ", " +
        " \"Content\" : " + Content->GetJSON(fileName) + " }";
}
