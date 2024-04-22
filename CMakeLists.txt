cmake_minimum_required(VERSION 3.26)
project(ddos-attacker C)

set(CMAKE_C_STANDARD 11)

add_executable(
        win_da windows/main.c
        usage.h
        usage.c
        environment.h
        environment.c
)

target_link_libraries(win_da ws2_32)
