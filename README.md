# kanjilearner
QT6 App for practicing how to write kanji using wacom tablets on Linux and a self-defined csv file for vocabulary you want to learn

# How to use
### get a graphics tablet
- the app uses the canvastablet example from qt for the drawing fields, which should™ work with any usb wacom tablet like the intuos small
### create a list of vocabulary
- change FILEPATH in src/CSVInteraction.h to the absolute filepath you want to store your list of vocabulary
- for the contents: use this as your template:
```
English,Japanese,lastTimePracticedSuccessfully,timesPracticedSuccessfully
I/Me/Myself,私,0,0
```
### change how many kanji you want to allow a vocabulary word to contain
- in `src/mainwindow.h` change CANVAS_COUNT to any value you want. On a scaled 28" 4k Display the max feels to be at around 7.
### compile
on arch:

`yay -S cmake rapidcsv qt6-main`

`cd $YOUR_GIT_CLONE_DIR`

`mkdir build`

`cd build`

`cmake ../CMakeLists.txt`

`make`

`./kanjilearner`
### how to use the GUI
- click next for loading the first entry in the csv
- read the english vocabulary name on the top of the GUI
- draw the kanji
