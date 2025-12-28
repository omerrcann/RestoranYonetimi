cmake_minimum_required(VERSION 3.10)


project(RestoranYonetim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/services/RestoranServisi.cpp
        src/entities/Masa.cpp
        src/entities/Garson.cpp
        src/entities/MenuKategori.cpp
        src/entities/MenuItem.cpp
        src/entities/Siparis.cpp
        src/entities/SiparisKalemi.cpp
        src/entities/Rezervasyon.cpp
)

add_executable(restoran_yonetim ${SOURCES})