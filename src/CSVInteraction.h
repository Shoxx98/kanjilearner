/**
 * File              : CSVInteraction.h
 * License           : see LICENSE.txt in the root dir. If there is none, it's GPLv3
 * Author            : Jonas Gilbricht <jonas.g.jobs@gmail.com>
 * Date              : 30.08.2026
 * Last Modified Date: 25.10.2026
 * Last Modified By  : Jonas Gilbricht <jonas.g.jobs@gmail.com>
 * Copyright (c) 2026 Jonas Gilbricht
 */
#ifndef __CSV_INTERACTION_H__
#define __CSV_INTERACTION_H__

#include <QtCore>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <qvariant.h>
#include <rapidcsv.h>
#include <string>
#include <vector>
/**
 TODO: make it so that you can just create CSVInteractor and use the file
straightaway
 TODO: get a random entry
**/

#define FILEPATH "/home/jonas/.local/share/kanjipracticer/vocablist.csv"

typedef struct {
    std::string vocabularyEnglish;
    std::string vocabularyJapanese;
    std::time_t lastTimePracticedSuccessfully;
    uint32_t timesPracticedSuccessfully;
    size_t entryRowIndex;
} CSVEntry;

struct CSVTable {
    int englishColIndex;
    std::vector<std::string> englishCol;

    int japaneseColIndex;
    std::vector<std::string> japaneseCol;

    int lastTimePracticedSuccessfullyIndex;
    std::vector<std::time_t> lastTimePracticedSuccessfullyCol;

    int timesPracticedSuccessfullyIndex;
    std::vector<uint32_t> timesPracticedSuccessfullyCol;

    size_t colSize;
};

struct CSVSubTable {
    struct CSVTable subTable;
    std::vector<unsigned int> indexMap;
};

class CSVInteractor {
  public:
    CSVInteractor();
    CSVInteractor(CSVInteractor &&)                 = default;
    CSVInteractor(const CSVInteractor &)            = default;
    CSVInteractor &operator=(CSVInteractor &&)      = default;
    CSVInteractor &operator=(const CSVInteractor &) = default;
    ~CSVInteractor();
    void printsomething();

    CSVEntry overwriteCurrentVocab();

    void raiseSomeCSVEntry();

  private:
    inline static CSVInteractor *owner = nullptr;
    CSVEntry currentVocab;
    rapidcsv::Document *_doc = nullptr;

    struct CSVTable doc;

    struct CSVSubTable dueVocab;

    bool checkSize();

    uint32_t getLowestSkillVal();
    bool currentVocabEqualsEntry();
    void getDueVocab();
    void getColumnIDs();
    void getColumns();
    void refreshVocab();
};

#endif // !__CSV_INTERACTION_H__
