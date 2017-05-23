cmake_minimum_required(VERSION 3.5)
project(aequatio)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMM_PLPLOT gtkmm-plplot-2.0)

include_directories(${GTKMM_INCLUDE_DIRS} ${GTKMM_PLPLOT_INCLUDE_DIRS})

set(SOURCE_FILES
        Aequatio.cpp
        MainWindow.hpp
        MainWindow.cpp
        EquationSystem.cpp
        EquationSystem.hpp
        )

add_executable(aequatio ${SOURCE_FILES})
target_link_libraries(aequatio ${GTKMM_LIBRARIES} ${GTKMM_PLPLOT_LIBRARIES})
