project(lpsmagic)

cmake_minimum_required(VERSION 2.6.2)

include(FindPkgConfig)

find_package(Qt4 4.7.3 REQUIRED QtCore )
pkg_check_modules(GCONF REQUIRED gconf-2.0)
pkg_check_modules(QMSYSTEM REQUIRED qmsystem2)

add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(icons)
add_subdirectory(qxtcore)