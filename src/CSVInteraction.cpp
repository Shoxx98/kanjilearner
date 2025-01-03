#include "CSVInteraction.h"
#include <cstdint>
#include <cstdlib>
#include <rapidcsv.h>
#include <random>

void CSVInteractor::getColumnIDs(){
    englishColIndex = _doc->GetColumnIdx("English");
    japaneseColIndex = _doc->GetColumnIdx("Japanese");
    lastTimePracticedSuccessfullyIndex = _doc->GetColumnIdx("lastTimePracticedSuccessfully");
    timesPracticedSuccessfullyIndex = _doc->GetColumnIdx("timesPracticedSuccessfully");
}

void CSVInteractor::getColumns(){
    englishCol = _doc->GetColumn<std::string>(englishColIndex);
    japaneseCol= _doc->GetColumn<std::string>(japaneseColIndex);
    lastTimePracticedSuccessfullyCol = _doc->GetColumn<time_t>(lastTimePracticedSuccessfullyIndex);
    timesPracticedSuccessfullyCol = _doc->GetColumn<uint32_t>(timesPracticedSuccessfullyIndex);
}

CSVInteractor::CSVInteractor(){
    if (this->owner != this && this->owner != nullptr) {
        delete this;
        return;
    }
    owner = this;
    this->_doc = new rapidcsv::Document(FILEPATH);

    std::srand(std::time(0));

    this->getColumnIDs();
    this->getColumns();

    this->checkSize();
}

CSVInteractor::~CSVInteractor(){
    if (this->owner == this) {
        owner = nullptr;
        return;
    }
    printf("WARNING: tried to have two objects of CSVInteraction, object destroyed itself\n");
}


void CSVInteractor::printsomething(){
    std::time_t time = std::time(0);
    printf("%lu\n", time);
}

CSVEntry CSVInteractor::overwriteCurrentCSVEntry(){
    // TODO: search for lowest value
    // TODO: search, starting at a random integer -> first match is somewhat random
    size_t firstLowestSkillVal = (1 << 31);
    size_t firstLowestSkillIndex = (1 << 31);

    size_t index = std::rand()%colSize;

    for (size_t i = 0; i < colSize; i++) {
        if (++index == colSize) {
           index = 0;
        }
        if (timesPracticedSuccessfullyCol[index] < firstLowestSkillVal) {
            firstLowestSkillVal = timesPracticedSuccessfullyCol[index];
            firstLowestSkillIndex = index;
        }
    }

    // std::srand(index);

    currentCSVEntry = {englishCol[firstLowestSkillIndex],
        japaneseCol[firstLowestSkillIndex],
        lastTimePracticedSuccessfullyCol[firstLowestSkillIndex],
        timesPracticedSuccessfullyCol[firstLowestSkillIndex],
        firstLowestSkillIndex};


    return currentCSVEntry;
}

void CSVInteractor::raiseSomeCSVEntry(){
    _doc->SetCell<std::time_t>(lastTimePracticedSuccessfullyIndex, currentCSVEntry.entryRowIndex, std::time(0));
    _doc->SetCell<uint32_t>(timesPracticedSuccessfullyIndex, currentCSVEntry.entryRowIndex, ++currentCSVEntry.timesPracticedSuccessfully);
    _doc->Save();
    this->getColumns();
    this->checkSize();
}


void CSVInteractor::checkSize(){
    colSize = englishCol.size();
    if (!(colSize == japaneseCol.size() &&
        colSize == lastTimePracticedSuccessfullyCol.size() &&
        colSize == timesPracticedSuccessfullyCol.size()))
    {
        printf("columns are of different sizes -> something went wrong in CSVInteractor::CSVInteractor\n");
    }
}
