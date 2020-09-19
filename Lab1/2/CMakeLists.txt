cmake_minimum_required(VERSION 3.15)
project(Lab1_2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5Widgets)

qt5_wrap_ui(QT_TEST_UI_HEADERS View/Windows/MainWindow.ui)

set(HEADERS
        ${QT_TEST_UI_HEADERS}
        View/Windows/MainWindow.h
        Logic/Logic.h)

set(DEFINITIONS
        main.cpp
        View/Windows/MainWindow.cpp
        Logic/Logic.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${DEFINITIONS})
qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
