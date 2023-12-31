cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)

project(stay-on)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(stay-on
  stay-on.c
)

target_link_libraries(stay-on
  pico_stdlib
  pico_cyw43_arch_none
)

pico_add_extra_outputs(stay-on)
