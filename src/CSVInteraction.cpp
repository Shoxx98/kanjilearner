#include "CSVInteraction.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <rapidcsv.h>

void CSVInteractor::getColumnIDs() {
    this->doc.englishColIndex  = _doc->GetColumnIdx("English");
    this->doc.japaneseColIndex = _doc->GetColumnIdx("Japanese");
    this->doc.lastTimePracticedSuccessfullyIndex =
        _doc->GetColumnIdx("lastTimePracticedSuccessfully");
    this->doc.timesPracticedSuccessfullyIndex =
        _doc->GetColumnIdx("timesPracticedSuccessfully");
}

void CSVInteractor::getColumns() {
    this->doc.englishCol =
        _doc->GetColumn<std::string>(this->doc.englishColIndex);
    this->doc.japaneseCol =
        _doc->GetColumn<std::string>(this->doc.japaneseColIndex);
    this->doc.lastTimePracticedSuccessfullyCol =
        _doc->GetColumn<time_t>(this->doc.lastTimePracticedSuccessfullyIndex);
    this->doc.timesPracticedSuccessfullyCol =
        _doc->GetColumn<uint32_t>(this->doc.timesPracticedSuccessfullyIndex);
}

void CSVInteractor::refreshVocab() {
    if (this->_doc != nullptr) {
        delete (this->_doc);
    }
    this->_doc = new rapidcsv::Document(FILEPATH);
    assert(this->_doc);

    this->getColumnIDs();
    this->getColumns();
    assert(this->checkSize());
    this->doc.colSize = this->doc.englishCol.size();
    this->getDueVocab();
}

CSVInteractor::CSVInteractor() {
    if (this->owner != this && this->owner != nullptr) {
        delete this;
        return;
    }
    owner = this;

    std::srand(std::time(0));
    this->refreshVocab();
}

CSVInteractor::~CSVInteractor() {
    if (this->owner == this) {
        owner = nullptr;
        return;
    }
    printf("WARNING: tried to have two objects of CSVInteraction, object "
           "destroyed itself\n");
}

void CSVInteractor::printsomething() {
    std::time_t time = std::time(0);
    printf("%lu\n", time);
}

uint32_t CSVInteractor::getLowestSkillVal() {
    uint32_t lowestSkillVal = UINT32_MAX;
    uint32_t currentSkillVal;
    size_t colSize = this->doc.colSize;
    for (size_t doc_iter = 0; doc_iter < colSize; doc_iter++) {
        currentSkillVal = this->doc.timesPracticedSuccessfullyCol[doc_iter];
        if (currentSkillVal < lowestSkillVal) {
            lowestSkillVal = currentSkillVal;
        }
    }
    return lowestSkillVal;
}

void CSVInteractor::getDueVocab() {
    unsigned int colSize = this->doc.colSize;

    this->dueVocab.subTable.englishCol.clear();
    this->dueVocab.subTable.japaneseCol.clear();
    this->dueVocab.subTable.lastTimePracticedSuccessfullyCol.clear();
    this->dueVocab.subTable.timesPracticedSuccessfullyCol.clear();

    this->dueVocab.subTable.englishColIndex  = this->doc.englishColIndex;
    this->dueVocab.subTable.japaneseColIndex = this->doc.japaneseColIndex;
    this->dueVocab.subTable.timesPracticedSuccessfullyIndex =
        this->doc.timesPracticedSuccessfullyIndex;
    this->dueVocab.subTable.lastTimePracticedSuccessfullyIndex =
        this->doc.lastTimePracticedSuccessfullyIndex;

    uint32_t lowestSkillVal = this->getLowestSkillVal();

    for (size_t doc_iter = 0; doc_iter < colSize; doc_iter++) {
        if (this->doc.timesPracticedSuccessfullyCol[doc_iter] ==
            lowestSkillVal) {
            this->dueVocab.indexMap.push_back(doc_iter);
            this->dueVocab.subTable.englishCol.push_back(
                this->doc.englishCol[doc_iter]);
            this->dueVocab.subTable.japaneseCol.push_back(
                this->doc.japaneseCol[doc_iter]);
            this->dueVocab.subTable.lastTimePracticedSuccessfullyCol.push_back(
                this->doc.lastTimePracticedSuccessfullyCol[doc_iter]);
            this->dueVocab.subTable.timesPracticedSuccessfullyCol.push_back(
                this->doc.timesPracticedSuccessfullyCol[doc_iter]);
        }
    }
    this->dueVocab.subTable.colSize = this->dueVocab.subTable.englishCol.size();
}

CSVEntry CSVInteractor::overwriteCurrentVocab() {
    // TODO: set from dueVocab with a random access
    unsigned int index = std::rand() % this->dueVocab.subTable.colSize;

    currentVocab = {
        .vocabularyEnglish  = this->dueVocab.subTable.englishCol[index],
        .vocabularyJapanese = this->dueVocab.subTable.japaneseCol[index],
        .lastTimePracticedSuccessfully =
            this->dueVocab.subTable.lastTimePracticedSuccessfullyCol[index],
        .timesPracticedSuccessfully =
            this->dueVocab.subTable.timesPracticedSuccessfullyCol[index],
        .entryRowIndex = this->dueVocab.indexMap[index]};

    return currentVocab;
}

bool CSVInteractor::currentVocabEqualsEntry() {
    return (_doc->GetCell<std::string>(this->doc.englishColIndex,
                                       currentVocab.entryRowIndex) ==
            currentVocab.vocabularyEnglish) &&
           (_doc->GetCell<std::string>(this->doc.japaneseColIndex,
                                       currentVocab.entryRowIndex) ==
            currentVocab.vocabularyJapanese) &&
           (_doc->GetCell<std::time_t>(
                this->doc.lastTimePracticedSuccessfullyIndex,
                currentVocab.entryRowIndex) ==
            currentVocab.lastTimePracticedSuccessfully) &&
           (_doc->GetCell<std::uint32_t>(
                this->doc.timesPracticedSuccessfullyIndex,
                currentVocab.entryRowIndex) ==
            currentVocab.timesPracticedSuccessfully);
}

void CSVInteractor::raiseSomeCSVEntry() {
    assert(currentVocabEqualsEntry());
    _doc->SetCell<std::time_t>(this->doc.lastTimePracticedSuccessfullyIndex,
                               currentVocab.entryRowIndex, std::time(0));
    _doc->SetCell<uint32_t>(this->doc.timesPracticedSuccessfullyIndex,
                            currentVocab.entryRowIndex,
                            ++currentVocab.timesPracticedSuccessfully);
    _doc->Save();
    this->refreshVocab();
    this->getColumns();
    this->getDueVocab();
    assert(this->checkSize());
}

bool CSVInteractor::checkSize() {
    size_t colSize = this->doc.englishCol.size();
    return (colSize == this->doc.japaneseCol.size()) &&
           (colSize == this->doc.lastTimePracticedSuccessfullyCol.size()) &&
           (colSize == this->doc.timesPracticedSuccessfullyCol.size());
}
