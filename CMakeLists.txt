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
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(libpqxx)
FetchContent_MakeAvailable(json)


add_executable(Country-Relocation-Ranking-System main.cpp
        src/language_data_collector.cpp
        src/life_quality_data_collector.cpp
        src/postgres_db_manager.cpp
        src/statistics_analyzer.cpp
        src/weather_data_collector.cpp
        src/UI.cpp
        src/i_data_collector.cpp
)

target_include_directories(Country-Relocation-Ranking-System
        PRIVATE ${CMAKE_SOURCE_DIR}/include
)

add_executable(tests
        src/i_data_collector.cpp
        src/weather_data_collector.cpp
        tests/test_main.cpp
        tests/test_coord_from_name.cpp
)

target_include_directories(tests
        PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(tests
        PRIVATE
        gtest
        gmock
        gtest_main
        nlohmann_json::nlohmann_json
        ${Boost_LIBRARIES}
)
target_link_libraries(Country-Relocation-Ranking-System PRIVATE pqxx)
target_link_libraries(Country-Relocation-Ranking-System PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Country-Relocation-Ranking-System PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Country-Relocation-Ranking-System PRIVATE ${Boost_LIBRARIES})

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE gtest gmock gtest_main nlohmann_json::nlohmann_json ${Boost_LIBRARIES})
target_link_libraries(tests PRIVATE Ws2_32)

enable_testing()
add_test(NAME tests COMMAND tests)
