cmake_minimum_required(VERSION 3.27)
project(smth)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/ASUS/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

include_directories(C:/Users/ASUS/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/include)
add_executable(smth main.cpp
        test_main.cpp
        test.cpp)

target_link_libraries(smth sfml-system sfml-window sfml-graphics sfml-network sfml-audio)



