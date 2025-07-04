cmake_minimum_required(VERSION 3.30)

project(Echoo-Server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(Echoo-Server
  main.cpp
  echooserver.h echooserver.cpp
  echoouser.h echoouser.cpp
  logger.h logger.cpp
  accountmanager.cpp accountmanager.h
  messagemanager.h messagemanager.cpp
  groupmanager.h groupmanager.cpp
  echoogroup.h echoogroup.cpp
)
target_link_libraries(Echoo-Server
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
)

include(GNUInstallDirs)
install(TARGETS Echoo-Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
