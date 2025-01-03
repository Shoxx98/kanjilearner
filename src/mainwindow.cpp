
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"
#include "tabletcanvas.h"

#include <QActionGroup>
#include <QApplication>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QGroupBox>
#include <charconv>
#include <cstdint>
#include <qfontinfo.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <QVBoxLayout>
#include <QRadioButton>
#include <string>

#include "mainwindow.h"

MainWindow *ptr;
// TODO: make it so you can translate in both directions
// TODO: make the window size dynamic so more vocabulary can be displayed

MainWindow::MainWindow(){
    lay = new QGridLayout(&central_widget);

    // resize(1500,800);

    ptr = this;

    QFont newFont = this->font();
    newFont.setPointSize(30);

    vocabDisplay.setFont(newFont);
    vocabDisplay.setFixedHeight(100);
    vocabDisplay.setText(csventry.vocabularyEnglish.c_str());
    vocabDisplay.setAlignment(Qt::AlignCenter);
    lay->addWidget(&vocabDisplay, 0, 0, 1,CANVAS_COUNT);

    newFont.setPointSize(160);

    const int fixedLength= 250;

    for (size_t i = 0; i < CANVAS_COUNT; i++) {
        QLabel *kanjiFieldArrPtr = &kanjiFieldArr[i];
        kanjiFieldArrPtr->setFont(newFont);
        // TODO: figure out how to make the font "full screen"
        // kanjiFieldArrPtr->setContentsMargins(-100,-100,-100,-100);
        kanjiFieldArrPtr->setFixedHeight(fixedLength);
        kanjiFieldArrPtr->setFixedWidth(fixedLength);
        kanjiFieldArrPtr->adjustSize();
        kanjiFieldArrPtr->setStyleSheet("background-color: rgb(255,255,255);");
        kanjiFieldArrPtr->setAlignment(Qt::AlignCenter);
        lay->addWidget(kanjiFieldArrPtr,1,i);
    }

    for (size_t i = 0; i < CANVAS_COUNT; i++) {
        canvasArr[i].setFixedHeight(fixedLength);
        canvasArr[i].setFixedWidth(fixedLength);
        lay->addWidget(&canvasArr[i],2,i);
    }

    QPushButton::connect(&nextBtn, &QPushButton::clicked, &(MainWindow::handleButtonNext));
    nextBtn.setText("Next");
    lay -> addWidget(&nextBtn);

    QPushButton::connect(&ResolveBtn, &QPushButton::clicked, &(MainWindow::handleButtonResolve));
    ResolveBtn.setText("Show Solution");
    lay->addWidget(&ResolveBtn);

    QPushButton::connect(&KnownBtn, &QPushButton::clicked, &(MainWindow::handleKnownButton));
    KnownBtn.setText("Knew the Solution");
    lay->addWidget(&KnownBtn);

    QPushButton::connect(&ClearBtn, &QPushButton::clicked, &(MainWindow::handleButtonClear));
    ClearBtn.setText("Clear Canvas");
    lay->addWidget(&ClearBtn);

    setCentralWidget(&central_widget);
    show();
}

void MainWindow::handleButtonNext(){

    ptr->csventry = ptr->csv.overwriteCurrentCSVEntry();
    ptr->vocabDisplay.setText(ptr->csventry.vocabularyEnglish.c_str());

    ptr->clearCanvas();

    for (size_t i = 0; i < CANVAS_COUNT; i++) {
        ptr->kanjiFieldArr[i].setStyleSheet("color: rgb(255,255,255);background-color: rgb(255,255,255);");
        if (QString(ptr->csventry.vocabularyJapanese.c_str())[i]!='\0') {
            ptr->kanjiFieldArr[i].setText(QString(ptr->csventry.vocabularyJapanese.c_str())[i]);
        }
        // QString wraps around while counting, so we need to handle the rest in one swoop
        else {
            for (size_t j = i; j < CANVAS_COUNT; j++) {
                ptr->kanjiFieldArr[j].setText("");
            }
            break;
        }
    }
}

void MainWindow::clearCanvas(){
    for (size_t i = 0; i < CANVAS_COUNT; i++) {
        canvasArr[i].clear();
    }
}

void MainWindow::handleButtonClear(){
    ptr->clearCanvas();
}

void MainWindow::handleButtonResolve(){
    for (size_t i = 0; i < CANVAS_COUNT; i++) {
        ptr->kanjiFieldArr[i].setStyleSheet("color: rgb(0,0,0);background-color: rgb(255,255,255);");
    }
}

void MainWindow::handleKnownButton(){
    ptr->csv.raiseSomeCSVEntry();
    ptr->csv.overwriteCurrentCSVEntry();
    ptr->handleButtonNext();
}
