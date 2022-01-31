cmake_minimum_required(VERSION 3.20)
set(MY_PROJECT_NAME "beast-issue-2221")
project("${MY_PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.79 REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_executable(main1 main.cpp)

set(LIBS Boost::boost Boost::system Boost::thread
        OpenSSL::SSL OpenSSL::Crypto
        Threads::Threads)

target_link_libraries(main1 PUBLIC ${LIBS})

