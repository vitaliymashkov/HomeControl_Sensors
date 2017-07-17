cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME BasicOTA_new)
project(${PROJECT_NAME})

register_hardware_platform(/home/vitaliy/.arduino15/packages/esp8266/hardware/esp8266/2.3.0)

set(${CMAKE_PROJECT_NAME}_SKETCH ${PROJECT_NAME}.ino)

link_directories(${ARDUINO_SDK}/libraries)


print_board_list()
print_programmer_list()


#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)

set(${CMAKE_PROJECT_NAME}_BOARD d1_mini)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyUSB0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)


generate_arduino_firmware(${CMAKE_PROJECT_NAME})
