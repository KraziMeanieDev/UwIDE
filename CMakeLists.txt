cmake_minimum_required(VERSION 3.16)
project(UwIDE VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the Qt installation path (adjust this path to your Qt installation)
set(Qt6_DIR "C:/Qt/6.8.0/mingw_64/lib/cmake/Qt6")

# Find the required Qt modules (Core, Gui, Quick)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

# Define the source files (just your main.cpp for now)
set(SOURCES
    src/main.cpp
)

# Define the executable
add_executable(UwIDE ${SOURCES})

# Link Qt libraries (Core, Gui, and Quick)
target_link_libraries(UwIDE Qt6::Core Qt6::Gui Qt6::Quick)

# Copy QML files to the build output directory (if you have QML files)
file(GLOB QML_FILES src/*.qml)
foreach(qml_file ${QML_FILES})
    configure_file(${qml_file} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()


# Enable automatic MOC processing for Qt classes (if needed)
# qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
# target_sources(UwIDE PRIVATE ${MOC_SOURCES})
