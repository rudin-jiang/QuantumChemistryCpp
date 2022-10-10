add_library(
    nhfint
    shell.cpp
    elembasis.cpp
    basisfile.cpp
)

target_include_directories(
    nhfint PUBLIC
    .
)