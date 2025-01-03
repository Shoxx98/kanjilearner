# ABSOLUTELY DO NOT USE THIS ON YOUR WORK PC
I am not a professional QT dev of any kind, this was meant as a small and fast QT project for me to get into learning kanji. The TabletCanvas class seems to have some memory issues which are likely exploitable.
# kanjilearner
QT6 App for practicing how to write kanji using wacom tablets on Linux and a self-defined csv file for vocabulary you want to learn

# How to use
### set up a graphics tablet
- the app uses the [canvastablet example](https://doc.qt.io/qt-6/qtwidgets-widgets-tablet-example.html) from qt for the drawing fields, which should™ work with any usb wacom tablet like the intuos small
- follow the setup [here](https://wiki.archlinux.org/title/Graphics_tablet)
- if you get a graphics tablet that is big enough, or use it only on one display, you can probably stay on wayland. If not, you would probably want to switch to a DM/WM that uses xorg instead of wayland, because the size of the tablet will not be enough for you to write something as detailed as kanji and you will not be able to constrain the display area the graphicstablet is mapped to to one screen easily.
### create a list of vocabulary
- change FILEPATH in src/CSVInteraction.h to the absolute filepath you want to store your list of vocabulary
- for the contents: use this as your template:
```
English,Japanese,lastTimePracticedSuccessfully,timesPracticedSuccessfully
I/Me/Myself,私,0,0
```
- seperate the rows with linebreaks and the columns with commas
- only set the english and the japanese vocabulary, set the last entries to 0 every time you create a row.
- dont add a space character after commas
- if the english vocabulary cell contains a space, it will automatically be surrounded with `"` characters. you dont need to add those yourself.
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
- click "show solution"
- manually check if you drew the kanji correctly. I would recommend looking up how to draw the kanji on [jisho.org](https://jisho.org/search/%E7%A7%81%20%23kanji) (see the stroke order section).
