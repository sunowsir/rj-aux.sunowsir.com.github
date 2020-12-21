cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(rj-aux) 

include_directories(src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Gui Network DBus REQUIRED)

qt5_add_resources(qrc_FILES image.qrc)

add_executable(rj-aux
    src/main.cpp
    src/mainwindow.cpp
    src/traywidget.cpp
    src/loginwidget.cpp
    src/showinfowidget.cpp
    ${qrc_FILES}
)

target_link_libraries(rj-aux
    PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network Qt5::DBus
) 
