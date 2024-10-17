

add_executable(sync main.cpp)

target_include_directories(sync
  PUBLIC
    ${CMAKE_SOURCE_DIR}/dbimpl
    ${CMAKE_SOURCE_DIR}/fmt/include
    ${MYSQL_INCLUDE_DIR})

target_link_libraries(sync
  PUBLIC
    dbimpl
    pthread)
