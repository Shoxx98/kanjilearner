#ifndef __CSV_INTERACTION_H__
#define __CSV_INTERACTION_H__

#include <QtCore>
#include <cstdint>
#include <qvariant.h>
#include <string>
#include <ctime>
#include <rapidcsv.h>
#include <vector>
/**
 TODO: make it so that you can just create CSVInteractor and use the file straightaway
 TODO: get a random entry
**/

#define FILEPATH "/home/jonas/.local/share/kanjipracticer/vocablist.csv"

typedef struct{
    std::string vocabularyEnglish;
    std::string vocabularyJapanese;
    std::time_t lastTimePracticedSuccessfully;
    uint32_t timesPracticedSuccessfully;
    size_t entryRowIndex;
} CSVEntry;

class CSVInteractor {
public:
    CSVInteractor();
    CSVInteractor(CSVInteractor &&) = default;
    CSVInteractor(const CSVInteractor &) = default;
    CSVInteractor &operator=(CSVInteractor &&) = default;
    CSVInteractor &operator=(const CSVInteractor &) = default;
    ~CSVInteractor();
    void printsomething();

    CSVEntry overwriteCurrentCSVEntry();

    void raiseSomeCSVEntry();

private:
    inline static CSVInteractor *owner = nullptr;
    CSVEntry currentCSVEntry;
    rapidcsv::Document *_doc;

    int englishColIndex;
    std::vector<std::string> englishCol;

    int japaneseColIndex;
    std::vector<std::string> japaneseCol;

    int lastTimePracticedSuccessfullyIndex;
    std::vector<std::time_t> lastTimePracticedSuccessfullyCol;

    int timesPracticedSuccessfullyIndex;
    std::vector<uint32_t> timesPracticedSuccessfullyCol;

    size_t colSize;

    void checkSize();

    void getColumnIDs();
    void getColumns();
};


#endif // !__CSV_INTERACTION_H__
