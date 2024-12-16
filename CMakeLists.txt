cmake_minimum_required(VERSION 3.16)

project(Uwide VERSION 1.0 LANGUAGES CXX)

# Enable Qt build helpers
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate Qt Quick
find_package(Qt6 COMPONENTS Quick REQUIRED)

# Standard Qt project setup
qt_standard_project_setup()

# List of source files
set(SOURCES
    src/main.cpp
    src/core/Explorer.cpp
    src/core/MenuController.cpp
)

# List of header files
set(HEADERS
    src/core/Explorer.h
    src/core/MenuController.h
)

# Define the executable
qt_add_executable(Uwide
    main.qrc
    ${SOURCES}
    ${HEADERS} 
)

# qt_policy(SET QTP0001 OLD)

# # Add QML module
# qt_add_qml_module(Uwide
#     URI Uwide
#     VERSION 1.0
#     QML_FILES main.qml
# )

# Optional resources
qt_add_resources(Uwide "resources"
    PREFIX "/"
    # FILES resources/icon.png resources/style.css
)

# Link Qt libraries
target_link_libraries(Uwide PRIVATE Qt6::Quick)

# Install target for easy deployment
install(TARGETS Uwide
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
