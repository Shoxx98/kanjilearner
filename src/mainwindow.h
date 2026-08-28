/**
 * File              : mainwindow.h
 * License           : see LICENSE.txt in the root dir. If there is none, it's GPLv3
 * Author            : Jonas Gilbricht <jonas.g.jobs@gmail.com>
 * Date              : 28.08.2026
 * Last Modified Date: 28.08.2026
 * Last Modified By  : Jonas Gilbricht <jonas.g.jobs@gmail.com>
 * Copyright (c) 2026 Jonas Gilbricht
 */

// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CSVInteraction.h"
#include "tabletcanvas.h"
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <cstdint>

#define CANVAS_COUNT 7

//! [0]
class MainWindow : public QMainWindow {
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
