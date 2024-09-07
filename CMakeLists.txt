cmake_minimum_required(VERSION 3.29) # FetchContent is available starting with CMake 3.11
project(City-Relocation-Ranking-System)

set(CMAKE_CXX_STANDARD 20)

set(PostgreSQL_INCLUDE_DIR "D:/PostgreSQL/16/include")
set(PostgreSQL_LIBRARY "D:/PostgreSQL/16/lib/libpq.lib")
set(CURL_INCLUDE_DIR "C:/Users/user/.vcpkg-clion/vcpkg/installed/x64-windows/include")
set(CURL_LIBRARY_DIR "C:/Users/user/.vcpkg-clion/vcpkg/installed/x64-windows/lib/libcurl.lib")

find_package(CURL REQUIRED)

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

add_executable(City-Relocation-Ranking-System
        main.cpp
        src/language_data_collector.cpp
        src/life_quality_data_collector.cpp
        src/postgres_db_manager.cpp
        src/weather_data_collector.cpp
        src/UI.cpp
        src/i_data_collector.cpp
        include/weather_analysis.h
        include/language_analysis.h
        include/life_quality_analysis.h
)

target_include_directories(City-Relocation-Ranking-System
        PRIVATE ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CURL_INCLUDE_DIR}
)

target_link_libraries(City-Relocation-Ranking-System
        PRIVATE libpqxx::pqxx
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE CURL::libcurl
)

add_executable(tests
        src/i_data_collector.cpp
        src/weather_data_collector.cpp
        tests/test_main.cpp
        tests/test_weather_data_collector.cpp
)

target_include_directories(tests
        PRIVATE ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CURL_INCLUDE_DIR}
)

target_link_libraries(tests
        PRIVATE gtest
        PRIVATE gmock
        PRIVATE gtest_main
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE CURL::libcurl
        PRIVATE Ws2_32
)

enable_testing()
add_test(NAME tests COMMAND tests)
