

add_executable(async main.cpp)

target_include_directories(async
  PUBLIC
    ${CMAKE_SOURCE_DIR}/dbimpl
    ${CMAKE_SOURCE_DIR}/fmt/include
    ${MYSQL_INCLUDE_DIR})

target_link_libraries(async
  PUBLIC
    dbimpl
    pthread)
