add_library(
    nhfMath
    vec3d.cpp
)

target_include_directories(
    nhfMath PUBLIC
    .
)


add_executable(
    main
    main.cpp
)

target_link_libraries(
    main PRIVATE
    nhfMath
)