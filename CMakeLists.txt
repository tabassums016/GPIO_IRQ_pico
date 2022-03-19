 
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "/home/tabassum/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

      # include(pico_sdk_import.cmake)

project(Pico-FreeRTOS)

# Add executable. Default name is the project name, version 0.1
add_executable(blink
       main.c
        )
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init() 
     
target_link_libraries(blink 
                      pico_stdlib )

pico_enable_stdio_uart(blink 0)
pico_enable_stdio_usb(blink 1)

pico_add_extra_outputs(blink)
