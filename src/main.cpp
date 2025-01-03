
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"
#include "tabletapplication.h"
#include "tabletcanvas.h"
#include <qapplication.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qmetacontainer.h>
#include <qnamespace.h>
#include <qsize.h>
#include <stdio.h>
#include <QPushButton>
#include "CSVInteraction.h"


// TODO: clear button on each field
// TODO: grid background for canvas
// TODO:

#include <QtWidgets>



int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    // TabletCanvas* ptr = &canvasArr[0];
    // ptr->resize(300,300);
    // ptr->move(0,0);


    return a.exec();
}
