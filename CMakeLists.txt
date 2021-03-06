cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(artillery)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# Fetch a version that only contains the necessary headers that automatically updates as new releases come out
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG        v3.9.1
)

# Adds json parsing library
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_library(json_lib INTERFACE)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

target_link_libraries(json_lib INTERFACE nlohmann_json::nlohmann_json)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.11.1
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES src/core/tank.cc
                              src/core/bullet.cc
                              src/core/terrain.cc
                              src/utilities/json_manager.cc
                              src/utilities/quadratic_model.cc)

list(APPEND UI_SOURCE_FILES src/ui/button.cc
                            src/ui/pause_menu.cc
                            src/ui/pause_button.cc
                            src/ui/click_button.cc
                            src/ui/progress_bar.cc
                            src/ui/toggle_button.cc)

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
                            ${UI_SOURCE_FILES}
                            src/game/ui_handler.cc
                            src/game/game_engine.cc
                            src/game/artillery_app.cc)

list(APPEND TEST_FILES tests/test_tank.cc
                       tests/test_bullet.cc
                       tests/test_quadratic_model.cc)

configure_file(data/game_settings.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/game_settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

ci_make_app(
        APP_NAME        artillery-main
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       json_lib
)

ci_make_app(
        APP_NAME        artillery-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2 json_lib
)

if(MSVC)
    set_property(TARGET artillery-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()
