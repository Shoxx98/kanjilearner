// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "tabletapplication.h"

// //! [0]
// // TODO: move setTabletDevice to widget
// bool TabletApplication::event(QEvent *event)
// {
//     if (event->type() == QEvent::TabletEnterProximity ||
//         event->type() == QEvent::TabletLeaveProximity) {
//         m_canvas->setTabletDevice(static_cast<QTabletEvent *>(event));
//         return true;
//     }
//     return QApplication::event(event);
// }
// //! [0]

// void TabletApplication::setCanvas(TabletCanvas *canvas, uint8_t arrSize){
// }
