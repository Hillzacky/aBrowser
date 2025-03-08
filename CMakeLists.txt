cmake_minimum_required(VERSION 3.10)
project(aBrowser)
set(CMAKE_CXX_STANDARD 17)
find_package(Qt5Widgets REQUIRED)
find_package(CEF REQUIRED)
add_executable(AntiDetectionBrowser
    main.cpp
    browser/browser.cpp browser/js_injector.cpp browser/res_handler.cpp
    settings/settings.cpp
    ui/main_window.cpp
    api/api.cpp
)
target_link_libraries(AntiDetectionBrowser Qt5::Widgets ${CEF_LIBRARIES})
