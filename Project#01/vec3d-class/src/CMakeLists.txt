add_library(
    nhfmath
    vec3d.cpp
)

target_include_directories(
    nhfmath PUBLIC
    .
)


add_executable(
    main
    main.cpp
)

target_link_libraries(
    main PRIVATE
    nhfmath
)