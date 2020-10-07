cmake_minimum_required(VERSION 3.15)
project(Lab2_1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stdc++fs UNKNOWN IMPORTED)
set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")

find_package(Qt5Widgets)
find_package(Qt5PrintSupport)

qt5_wrap_ui(QT_TEST_UI_HEADERS View/Windows/MainWindow.ui)

set(WIDGET_DIR View/Widget/QCustomPlot/)

set(HEADERS
        ${QT_TEST_UI_HEADERS}
        Handler/Handler.h
        Logic/Logic.h
        View/Widget/QCustomPlot/qcustomplot.h
        View/Windows/MainWindow.h)

set(DEFINITIONS
        main.cpp
        Handler/Handler.cpp
        Logic/Logic.cpp
        View/Widget/QCustomPlot/qcustomplot.cpp
        View/Windows/MainWindow.cpp)

include_directories(${WIDGET_DIR})
add_executable(${PROJECT_NAME} ${HEADERS} ${DEFINITIONS})
qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} stdc++fs ${QT_LIBRARIES} ${OPENGL_LIBRARIES} Qt5::PrintSupport)
