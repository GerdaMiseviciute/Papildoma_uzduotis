cmake_minimum_required(VERSION 3.10)
project(Papildoma_uzduotis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ICU paths (MSYS2 MinGW)
set(ICU_ROOT "C:/msys64/mingw64")

include_directories(${ICU_ROOT}/include)
link_directories(${ICU_ROOT}/lib)

add_executable(Objektinis-programavimas main.cpp)

# ICU libraries (IMPORTANT ORDER)
target_link_libraries(Objektinis-programavimas
    icuuc
    icuin
    icudt
)