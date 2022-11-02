#include "CAFFCredits.h"

CAFFCredits::CAFFCredits(vector<unsigned char>::const_iterator const& creditsInput) {
    auto iterator = creditsInput;
    
    ID = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Length = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;

    Year = vector<unsigned char>{ iterator, iterator + 2 };
    iterator += 2;

    Month = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Day = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Hour = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    Minute = vector<unsigned char>{ iterator, iterator + 1 };
    ++iterator;

    CreatorLen = vector<unsigned char>{ iterator, iterator + 8 };
    iterator += 8;
    
    Creator = vector<unsigned char>{ iterator, iterator + ConvertToInt(CreatorLen) };
}

int CAFFCredits::ConvertToInt(vector<unsigned char> const& toConvert) {
    int toReturn = 0;
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i] * pow(16, i * 2);
    }
    return toReturn;
}

string CAFFCredits::ConvertToString(vector<unsigned char> const& toConvert) {
    string toReturn = "";
    for (size_t i = 0; i < toConvert.size(); ++i) {
        toReturn += toConvert[i];
    }
    return toReturn;
}

int CAFFCredits::GetID() {
    return ConvertToInt(ID);
}

int CAFFCredits::GetLength() {
    return ConvertToInt(Length);
}

int CAFFCredits::GetYear() {
    return ConvertToInt(Year);
}

int CAFFCredits::GetMonth() {
    return ConvertToInt(Month);
}

int CAFFCredits::GetDay() {
    return ConvertToInt(Day);
}

int CAFFCredits::GetHour() {
    return ConvertToInt(Hour);
}

int CAFFCredits::GetMinute() {
    return ConvertToInt(Minute);
}

int CAFFCredits::GetCreatorLen() {
    return ConvertToInt(CreatorLen);
}

vector<unsigned char> CAFFCredits::GetCreator() {
    return Creator;
}

bool CAFFCredits::IsValid() {
    //TODO
    return true;
}

string CAFFCredits::GetJSON() {
    return "{ \"ID\" : " + to_string(ConvertToInt(ID)) + ", " +
        "\"Length\" : " + to_string(ConvertToInt(Length)) + ", " +
        "\"Year\" : " + to_string(ConvertToInt(Year)) + ", " +
        "\"Month\" : " + to_string(ConvertToInt(Month)) + ", " +
        "\"Day\" : " + to_string(ConvertToInt(Day)) + ", " +
        "\"Hour\" : " + to_string(ConvertToInt(Hour)) + ", " +
        "\"Minute\" : " + to_string(ConvertToInt(Minute)) + ", " +
        "\"CreatorLen\" : " + to_string(ConvertToInt(CreatorLen)) + ", " +
        "\"Creator\" : \"" + ConvertToString(Creator) + "\" }";;
}
