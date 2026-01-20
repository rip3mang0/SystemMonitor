cmake_minimum_required(VERSION 3.16)

project(SystemMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(TS_FILES SystemMonitor_en_001.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        systemmonitor.h
        systemmonitor.cpp

        utils/systeminfo.h
        utils/formatters.h

        widgets/infocard.h
        widgets/infocard.cpp
        widgets/chartwidget.h
        widgets/chartwidget.cpp
        ${TS_FILES}
)

#Platform specific sources
if(WIN32)
    list(APPEND PROJECT_SOURCES utils/systeminfo_win.cpp)
elseif(APPLE)
    list(APPEND PROJECT_SOURCES utils/systeminfo_mac.cpp)
elseif(UNIX)
    list(APPEND PROJECT_SOURCES utils/systeminfo_linux.cpp)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SystemMonitor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        widgets/infocard.h widgets/infocard.cpp
        widgets/chartwidget.h widgets/chartwidget.cpp
    )
    # Add resources (icons)
    qt_add_resources(SystemMonitor "icons"
        PREFIX "/icons"
        FILES
            resources/icons/app-icon.png
            resources/icons/cpu.png
            resources/icons/memory.png
            resources/icons/disk.png
            resources/icons/network.png
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SystemMonitor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(SystemMonitor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SystemMonitor
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(SystemMonitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#Platform-specific libraries
if(WIN32)
    target_link_libraries(SystemMonitor PRIVATE pdh iphlpapi psapi)
elseif(APPLE)
    target_link_libraries(SystemMonitor PRIVATE "-framework IOKit" "-framework Foundation")
target_link_libraries(SystemMonitor PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SystemMonitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SystemMonitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SystemMonitor)
endif()
set_target_properties(SystemMonitor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SystemMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SystemMonitor)
endif()
