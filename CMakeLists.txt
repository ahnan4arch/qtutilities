cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# meta data
set(META_PROJECT_NAME qtutilities)
set(META_PROJECT_VARNAME QT_UTILITIES)
set(META_APP_NAME "Qt Utilities")
set(META_APP_AUTHOR "Martchus")
set(META_APP_URL "https://github.com/${META_APP_AUTHOR}/${META_PROJECT_NAME}")
set(META_APP_DESCRIPTION "Common Qt related C++ classes and routines used by my applications such as dialogs, widgets and models")
set(META_VERSION_MAJOR 5)
set(META_VERSION_MINOR 4)
set(META_VERSION_PATCH 0)
set(META_APP_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})

# add project files
set(HEADER_FILES
    misc/xmlparsermacros.h
    misc/undefxmlparsermacros.h
    misc/trylocker.h
    misc/adoptlocker.h
    misc/dialogutils.h
    misc/desktoputils.h
    misc/conversion.h
    models/checklistmodel.h
    resources/qtconfigarguments.h
    resources/resources.h
    resources/importplugin.h
)
set(SRC_FILES
    misc/dialogutils.cpp
    misc/desktoputils.cpp
    models/checklistmodel.cpp
    resources/qtconfigarguments.cpp
    resources/resources.cpp
    resources/qtutilsicons.qrc
)

set(WIDGETS_HEADER_FILES
    aboutdialog/aboutdialog.h
    enterpassworddialog/enterpassworddialog.h
    settingsdialog/optioncategory.h
    settingsdialog/optioncategoryfiltermodel.h
    settingsdialog/optioncategorymodel.h
    settingsdialog/optionpage.h
    settingsdialog/settingsdialog.h
    settingsdialog/qtsettings.h
    widgets/buttonoverlay.h
    widgets/clearcombobox.h
    widgets/clearlineedit.h
    widgets/clearplaintextedit.h
    widgets/clearspinbox.h
    widgets/iconbutton.h
    widgets/pathselection.h
    paletteeditor/paletteeditor.h
    paletteeditor/colorbutton.h
    misc/recentmenumanager.h
)
set(WIDGETS_SRC_FILES
    aboutdialog/aboutdialog.cpp
    enterpassworddialog/enterpassworddialog.cpp
    settingsdialog/optioncategory.cpp
    settingsdialog/optioncategoryfiltermodel.cpp
    settingsdialog/optioncategorymodel.cpp
    settingsdialog/optionpage.cpp
    settingsdialog/settingsdialog.cpp
    settingsdialog/qtsettings.cpp
    widgets/buttonoverlay.cpp
    widgets/clearcombobox.cpp
    widgets/clearlineedit.cpp
    widgets/clearplaintextedit.cpp
    widgets/clearspinbox.cpp
    widgets/iconbutton.cpp
    widgets/pathselection.cpp
    paletteeditor/paletteeditor.cpp
    paletteeditor/colorbutton.cpp
    misc/recentmenumanager.cpp
)
set(WIDGETS_UI_FILES
    aboutdialog/aboutdialog.ui
    enterpassworddialog/enterpassworddialog.ui
    settingsdialog/settingsdialog.ui
    settingsdialog/qtappearanceoptionpage.ui
    settingsdialog/qtlanguageoptionpage.ui
    settingsdialog/qtenvoptionpage.ui
    paletteeditor/paletteeditor.ui
)

set(CMAKE_MODULE_FILES
    cmake/modules/QtConfig.cmake
    cmake/modules/QtGuiConfig.cmake
    cmake/modules/QtLinkage.cmake
    cmake/modules/JsProviderConfig.cmake
    cmake/modules/WebViewProviderConfig.cmake
)

set(TS_FILES
    translations/${META_PROJECT_NAME}_de_DE.ts
    translations/${META_PROJECT_NAME}_en_US.ts
)

set(DOC_FILES
    README.md
)

set(REQUIRED_ICONS
    dialog-cancel
    dialog-ok
    dialog-ok-apply
    document-open
    document-open-recent
    edit-clear
    go-next
    preferences-desktop-icons
    preferences-desktop-locale
    qtcreator
    system-file-manager
    system-run
    system-search
    window-close
)

set(SCRIPT_FILES
    scripts/required_icons.sh
)

# required to include CMake modules from own project directory
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" "${CMAKE_MODULE_PATH}")

# configure platform specific capslock detection
if(WIN32)
    # WinAPI provides functions required for capslock detection
    list(APPEND META_PRIVATE_COMPILE_DEFINITIONS QT_UTILITIES_PLATFORM_SPECIFIC_CAPSLOCK_DETECTION)
else()
    # X11 can provide functions required for capslock detection under non-Windows environments
    find_package(X11)
    if(X11_FOUND)
        list(APPEND LIBRARIES ${X11_LIBRARIES})
        list(APPEND META_PRIVATE_COMPILE_DEFINITIONS QT_UTILITIES_PLATFORM_SPECIFIC_CAPSLOCK_DETECTION)
    endif()
endif()

# configure support for D-Bus notifications
option(DBUS_NOTIFICATIONS "enables support for D-Bus notifications" ${UNIX})
set(DBUS_NOTIFICATIONS_FILE_NAME misc/dbusnotification)
if(DBUS_NOTIFICATIONS)
    list(APPEND HEADER_FILES
        ${DBUS_NOTIFICATIONS_FILE_NAME}.h
    )
    list(APPEND SRC_FILES
        ${DBUS_NOTIFICATIONS_FILE_NAME}.cpp
    )
    list(APPEND DBUS_FILES
        dbus/org.freedesktop.Notifications.xml
    )
    list(APPEND META_PUBLIC_COMPILE_DEFINITIONS ${META_PROJECT_VARNAME}_SUPPORT_DBUS_NOTIFICATIONS)
    message(STATUS "D-Bus notifications enabled")
else()
    list(APPEND DOC_ONLY_FILES
        ${DBUS_NOTIFICATIONS_FILE_NAME}.h
        ${DBUS_NOTIFICATIONS_FILE_NAME}.cpp
    )
    message(STATUS "D-Bus notifications disabled")
endif()

# find c++utilities
find_package(c++utilities 4.5.0 REQUIRED)
use_cpp_utilities()

# include modules to apply configuration
include(BasicConfig)
include(QtGuiConfig)
set(META_PUBLIC_QT_MODULES Core ${ADDITIONAL_QT_MODULES})
include(QtConfig)
include(WindowsResources)
include(LibraryTarget)
include(Doxygen)
include(ConfigHeader)
