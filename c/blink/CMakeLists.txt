cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)

project(aya)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(aya 
  aya.c
)

target_link_libraries(aya pico_stdlib)
pico_add_extra_outputs(aya)
