cmake_minimum_required(VERSION 3.11) # FetchContent is available starting with CMake 3.11
project(Country-Relocation-Ranking-System)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "C:/Users/user/Desktop/boost_1_86_0")

find_package(Boost)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif()

include(FetchContent)

# Fetching libs
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main 
)

FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG        master
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG: v3.11.2
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(libpqxx)
FetchContent_MakeAvailable(json)

add_executable(tests tests/test_main.cpp)
add_executable(Country-Relocation-Ranking-System main.cpp)

target_link_libraries(tests PRIVATE gtest_main)
target_link_libraries(Country-Relocation-Ranking-System PRIVATE pqxx)
target_link_libraries(Country-Relocation-Ranking-System PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Country-Relocation-Ranking-System PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(Country-Relocation-Ranking-System PRIVATE ${Boost_LIBRARIES})

enable_testing()
add_test(NAME my_tests COMMAND my_tests)
