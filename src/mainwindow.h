
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CSVInteraction.h"
#include <QLabel>
#include "tabletcanvas.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <cstdint>

#define CANVAS_COUNT 7

//! [0]
class MainWindow : public QMainWindow
{
    // Q_OBJECT

public:
    MainWindow();

private slots:

    static void handleButtonNext();
    static void handleButtonResolve();
    static void handleKnownButton();
    static void handleButtonClear();

private:
    CSVEntry csventry;
    TabletCanvas canvasArr[CANVAS_COUNT];
    QLabel kanjiFieldArr[CANVAS_COUNT];
    QWidget central_widget;
    QGridLayout *lay;
    QLabel vocabDisplay;
    QPushButton nextBtn, ResolveBtn, KnownBtn, ClearBtn;
    CSVInteractor csv;

    void clearCanvas();
};
//! [0]

#endif
