cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME BasicOTA_new)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH BasicOTA_new.ino)

register_hardware_platform(${ARDUINO_SDK_PATH}/esp8266com/esp8266/)

link_directories(${ARDUINO_SDK}/libraries)

#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)

print_board_list()

set(${CMAKE_PROJECT_NAME}_BOARD esp)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyUSB0)
set(mega.build.mcu esp8266)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)


generate_arduino_firmware(${CMAKE_PROJECT_NAME})

