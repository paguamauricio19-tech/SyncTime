cmake_minimum_required(VERSION 3.13.4)

project(SyncTime)

find_package(Geode REQUIRED)

add_geode_mod(
    SyncTime
    ${MOD_ID}
    SOURCES
     main.cpp
)
