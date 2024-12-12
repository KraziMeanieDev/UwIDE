cmake_minimum_required(VERSION 3.16)

project(Uwide VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Quick REQUIRED)

qt_standard_project_setup()

qt_add_executable(Uwide
    main.cpp
)

qt_add_qml_module(Uwide
    URI Uwide
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(Uwide PRIVATE Qt6::Quick)

# Install target for easy deployment
install(TARGETS Uwide DESTINATION bin)
