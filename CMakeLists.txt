cmake_minimum_required(VERSION 3.8)
project(Online_converter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 REQUIRED COMPONENTS
    Widgets
    Core
    Gui
    Network
)

set(PROJECT_SOURCE
    main.cpp
    main_window.cpp
    main_window.h
    about.cpp
    about.h
    currency.cpp
    currency.h
    request_manager.cpp
    request_manager.h
    load_screen.cpp
    load_screen.h
    save_data.cpp
    save_data.h
    )

qt5_add_resources(PROJECT_RESOURCE Resource.qrc)
add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCE} ${PROJECT_RESOURCE})	
target_link_libraries(${PROJECT_NAME} PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
  )
