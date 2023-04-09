cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_SDK_PATH "../../pico-sdk")
include(pico_sdk_import.cmake)
project(badger2040)

pico_sdk_init()

include_directories(./board)

# generate an executable file
add_executable(${PROJECT_NAME}
    board/badger2040.cpp
    board/drivers/uc8151_legacy/uc8151_legacy.cpp
    board/libraries/hershey_fonts/hershey_fonts.cpp
    board/libraries/hershey_fonts/hershey_fonts_data.cpp
    board/libraries/bitmap_fonts/bitmap_fonts.cpp
    src/font.cpp
    src/main.cpp
)

pico_set_program_name(${PROJECT_NAME} "Pico Badger2040 Test")
pico_set_program_version(${PROJECT_NAME} "0.1")

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pwm hardware_spi)

pico_add_extra_outputs(${PROJECT_NAME})
