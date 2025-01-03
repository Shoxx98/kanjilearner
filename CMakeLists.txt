# cmake_minimum_required(VERSION 3.16)
#
# project(helloworld VERSION 1.0.0 LANGUAGES CXX)
#
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_COMPILE_COMMANDS ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
# # set(CMA)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# qt_standard_project_setup()
#
# qt_add_executable(helloworld
#     src/mainwindow.ui
#     src/mainwindow.cpp
#     src/main.cpp
# )
#
# target_link_libraries(helloworld PRIVATE Qt6::Widgets)
#
# set_target_properties(helloworld PROPERTIES
#     WIN32_EXECUTABLE ON
#     MACOSX_BUNDLE ON
# )

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(kanjilearner LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

qt_add_executable(kanjilearner
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/tabletapplication.cpp
    src/tabletapplication.h
    src/tabletcanvas.cpp
    src/tabletcanvas.h
    src/CSVInteraction.h
    src/CSVInteraction.cpp
)

set_target_properties(kanjilearner PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(kanjilearner PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Resources:
set(images_resource_files
    "images/cursor-airbrush.png"
    "images/cursor-eraser.png"
    "images/cursor-felt-marker.png"
    "images/cursor-pencil.png"
)

qt_add_resources(kanjilearner "images"
    PREFIX
        "/"
    FILES
        ${images_resource_files}
)

install(TARGETS kanjilearner
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET kanjilearner
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

