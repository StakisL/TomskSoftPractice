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
<<<<<<< HEAD
<<<<<<< HEAD
    request_api.cpp
    request_api.h
=======
    parse.cpp
    parse.h
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
=======
    parse.cpp
    parse.h
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
    )

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCE})	
target_link_libraries(${PROJECT_NAME} PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
  )
