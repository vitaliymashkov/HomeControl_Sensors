cmake_minimum_required(VERSION 2.8.4)

set(ESP8266_PLATFORM_PATH /home/vitaliy/.arduino15/packages/esp8266/hardware/esp8266/2.3.0)
set(USER_LIBS /home/vitaliy/Arduino/libraries)

set(ARDUINO_VERSION_PATH ${ESP8266_PLATFORM_PATH}/tools/sdk/version)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/Esp8266Toolchain.cmake)
set(PROJECT_NAME BasicOTA_new)
project(${PROJECT_NAME})

register_hardware_platform(${ESP8266_PLATFORM_PATH})

set(${CMAKE_PROJECT_NAME}_BOARD d1_mini)
message("Selected board: ${${CMAKE_PROJECT_NAME}_BOARD}")


message("Arduino version: ${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR}")

message("ESP8266 PLATFORM PATH: ${ESP8266_PLATFORM_PATH}")
message("USER_LIBS: ${USER_LIBS}")
message("Arduino SDK: ${ARDUINO_SDK}")
message("Arduino SDK path: ${ARDUINO_SDK_PATH}")
message("Arduino paths: ${ARDUINO_PATHS}")
message("Arduino SDK version: ${ARDUINO_SDK_VERSION}")

set(${CMAKE_PROJECT_NAME}_SKETCH ${PROJECT_NAME}.ino)

include_directories(${ESP8266_PLATFORM_PATH}/tools/sdk/include/)
include_directories(${USER_LIBS})

print_board_list()
print_programmer_list()


#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)

set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyUSB0)
set(${${CMAKE_PROJECT_NAME}_BOARD}.build.mcu atmega328)
set(${${CMAKE_PROJECT_NAME}_BOARD}.upload.protocol wiring)
set(${${CMAKE_PROJECT_NAME}_BOARD}.upload.speed 9600)


generate_arduino_firmware(${CMAKE_PROJECT_NAME})
