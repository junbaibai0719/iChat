cmake_minimum_required(VERSION 3.16)

project(iChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
#set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_AUTORCC ON)

set(QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/qml" CACHE STRING "qml import path")

add_subdirectory(qml/componentLib)

#if (WIN32)
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/iChat.rc")
#endif()
find_package(Qt6 REQUIRED
    COMPONENTS Quick QuickControls2 Sql)


qt_add_executable(appiChat
    main.cpp
        treeitem.h treeitem.cpp
        message_handler.h    message_handler.cpp
        treemodel.h treemodel.cpp
        treecolumn.h treecolumn.cpp
        db/SqlExecutor.h db/SqlExecutor.cpp
    ${app_icon_resource_windows}
)

qt_add_big_resources(SOURCES iChat.qrc)
target_sources(appiChat PRIVATE ${SOURCES})


qt_add_qml_module(appiChat
    URI iChat
    VERSION 1.0
    QML_FILES
        main.qml
        TestJsonModel.qml
        VideoPlayer.qml
    NO_RESOURCE_TARGET_PATH
#    SOURCEs
#        treeitem.h treeitem.cpp
#        message_handler.h    message_handler.cpp
#        treemodel.h treemodel.cpp
#        treecolumn.h treecolumn.cpp
#    RESOURCES
#        icons/logo.png
#        qtquickcontrols2.conf
)


set_target_properties(appiChat PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appiChat
    PRIVATE QT_MESSAGELOGCONTEXT
)

target_link_libraries(appiChat
    PRIVATE
    componentLib
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
)

install(TARGETS appiChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
