#include "CAFFCredits.h"

CAFFCredits::CAFFCredits(vector<unsigned char>::const_iterator const& creditsInput, int inputSize) {
    //Before start check.
    if (inputSize) {
        auto iterator = creditsInput;

        ID = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Length = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        Year = vector<unsigned char>{ iterator, iterator + 2 };
        iterator += 2;
        inputSize -= 8;

        Month = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Day = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Hour = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        Minute = vector<unsigned char>{ iterator, iterator + 1 };
        ++iterator;
        --inputSize;

        CreatorLen = vector<unsigned char>{ iterator, iterator + 8 };
        iterator += 8;
        inputSize -= 8;

        if (inputSize > ConvertToInt(CreatorLen)) {
            Creator = vector<unsigned char>{ iterator, iterator + ConvertToInt(CreatorLen) };
        }
    }
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
    bool isValid = true;

    if (ID.size() != 1 || ConvertToInt(ID) != 2) {
        isValid = false;
    }
    if (Length.size() != 8) {
        isValid = false;
    }
    if (Year.size() != 2) {
        isValid = false;
    }
    if (Month.size() != 1) {
        isValid = false;
    }
    if (Day.size() != 1) {
        isValid = false;
    }
    if (Hour.size() != 1) {
        isValid = false;
    }
    if (Minute.size() != 1) {
        isValid = false;
    }
    if (CreatorLen.size() != 8) {
        isValid = false;
    }
    if (Creator.size() != ConvertToInt(CreatorLen)) {
        isValid = false;
    }

    return isValid;
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
