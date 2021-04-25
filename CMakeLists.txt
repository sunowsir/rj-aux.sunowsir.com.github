cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(rj-aux) 

include_directories(src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../opt/rjsupplicant-aux/)

find_package(Qt5 COMPONENTS Core Widgets Gui Network DBus REQUIRED)

qt5_add_resources(qrc_FILES image.qrc)

add_executable(rj-aux
    src/main.cpp
    src/mainwindow.cpp
    src/traywidget.cpp
    src/loginwidget.cpp
    src/showinfowidget.cpp
    src/setting_window.cpp
    src/setting_widget.cpp
    ${qrc_FILES}
)

target_link_libraries(rj-aux
    PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network Qt5::DBus
) 

install(TARGETS 
    rj-aux
    RUNTIME DESTINATION bin
)

install(FILES
    opt/rjsupplicant-aux/notify DESTINATION bin
    PERMISSIONS 
        OWNER_READ 
        OWNER_WRITE 
        OWNER_EXECUTE 
        GROUP_READ 
        GROUP_EXECUTE 
        WORLD_READ
        WORLD_EXECUTE
)

install(FILES
    opt/rjsupplicant-aux/getLastAccount DESTINATION bin
    PERMISSIONS 
        OWNER_READ 
        OWNER_WRITE 
        OWNER_EXECUTE 
        GROUP_READ 
        GROUP_EXECUTE 
        WORLD_READ
        WORLD_EXECUTE
)

install(FILES
    opt/rjsupplicant-aux/rjsupplicant.start DESTINATION bin
    PERMISSIONS 
        OWNER_READ 
        OWNER_WRITE 
        OWNER_EXECUTE 
        GROUP_READ 
        GROUP_EXECUTE 
        WORLD_READ
        WORLD_EXECUTE
)

install(FILES
    lib/libssl.so.6 DESTINATION lib/rjsupplicant/
)

install(FILES
    lib/libcrypto.so.6 DESTINATION lib/rjsupplicant/
)

install(FILES
    lib/libpcap.so.0.9 DESTINATION lib/rjsupplicant/
)

install(FILES
    usr/share/pixmaps/rj-aux.png DESTINATION share/pixmaps/
)

install(FILES
    usr/share/polkit-1/actions/org.rj-aux.campus-network.policy DESTINATION share/polkit-1/actions/org.rj-aux.campus-network.policy
)

install(FILES
    usr/share/applications/rjsupplicant-aux.desktop DESTINATION share/applications/rjsupplicant-aux.desktop
)




