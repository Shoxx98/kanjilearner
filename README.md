# kanjilearner
QT6 App for practicing how to write kanji using wacom tablets on Linux and a self-defined csv file for vocabulary you want to learn

# How to use
### create a list of vocabulary
- change FILEPATH in src/CSVInteraction.h to the absolute filepath you want to store your list of vocabulary
- for the contents: use this as your template:
```
English,Japanese,lastTimePracticedSuccessfully,timesPracticedSuccessfully
I/Me/Myself,私,0,0
```
### compile
on arch:

`yay -S cmake rapidcsv qt6-main`

`cd $YOUR_GIT_CLONE_DIR`

`mkdir build`

`cd build`

`cmake ../CMakeLists.txt`

`make`

`./kanjilearner`
