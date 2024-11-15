cmake_minimum_required(VERSION 3.16)
project(UwIDE VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the Qt installation path (adjust this path to your Qt installation)
set(Qt6_DIR "C:/Qt/6.8.0/mingw_64/lib/cmake/Qt6")

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Define the source files
set(SOURCES
    src/main.cpp
    src/AppWindow.cpp
    src/panels/editor/EditorWidget.cpp
    src/panels/editor/EditorWindow.cpp
)

# Define the header files
set(HEADERS
    src/AppWindow.h
    src/panels/editor/EditorWidget.h
    src/panels/editor/EditorWindow.h
)

# Add component-specific sources (like custom UI components)
file(GLOB_RECURSE COMPONENT_SOURCES
    components/*/*.cpp
)

file(GLOB_RECURSE COMPONENT_HEADERS
    components/*/*.h
)

# Add all source and header files to the target
list(APPEND SOURCES ${COMPONENT_SOURCES})
list(APPEND HEADERS ${COMPONENT_HEADERS})

# Wrap headers with Q_OBJECT
qt6_wrap_cpp(MOC_SOURCES ${HEADERS} ${COMPONENT_HEADERS})

# Define the executable
add_executable(UwIDE ${SOURCES} ${HEADERS} ${MOC_SOURCES})

# Link Qt libraries
target_link_libraries(UwIDE Qt6::Core Qt6::Gui Qt6::Widgets)

# Enable testing if needed
# enable_testing()

# Install the executable (optional, if you want to support installation)
# install(TARGETS UwIDE DESTINATION bin)
