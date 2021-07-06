cmake_minimum_required(VERSION 3.17.5)
project(qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:\\Cursuri\\qt\\5.15.2\\mingw81_64\\lib\\cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
include_directories(domain)
include_directories(repository)
include_directories(observer)
include_directories(gui)

find_package(Qt5Widgets REQUIRED)
add_executable(qt
        domain/Ethnologist.cpp
        domain/Ethnologist.h
        domain/Building.cpp
        domain/Building.h
        repository/Repository.h
        observer/Observer.h
        repository/EthnologistRepository.cpp
        repository/EthnologistRepository.h
        repository/BuildingRepository.cpp
        repository/BuildingRepository.h
        gui/AbstractModel.cpp
        gui/AbstractModel.h
        gui/GUI.cpp
        gui/GUI.h)


target_link_libraries(qt Qt5::Widgets)