cmake_minimum_required(VERSION 3.16)

project(componentLib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
#set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(Qt6 REQUIRED COMPONENTS Quick)

#qt_add_library(componentLib STATIC)
#qt_add_library(componentLib SHARED)
qt_add_qml_module(componentLib
    URI componentLib
    VERSION 1.0
    QML_FILES
        ShadowRectangle.qml
        Buttons/FlatButton.qml
        DatePicker.qml
        ElMonthGrid.qml
        Link.qml
)

set_target_properties(componentLib PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(componentLib
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(componentLib
    PRIVATE
    Qt6::Quick
)

target_include_directories(componentLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


