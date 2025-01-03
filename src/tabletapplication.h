// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef TABLETAPPLICATION_H
#define TABLETAPPLICATION_H

#include <QApplication>
#include <cstdint>

#include "tabletcanvas.h"

//! [0]
class TabletApplication : public QApplication
{
    Q_OBJECT

public:
    using QApplication::QApplication;


private:
    // getting pointer issues with this
};
//! [0]

#endif
