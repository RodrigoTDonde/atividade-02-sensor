# Preserve o nome completo do executavel no caminho curto do Windows.
# CMake converte um caminho com espacos para um nome 8.3 de executavel;
# isso impede o GCC Xtensa de identificar corretamente o ESP32-S3.
include($ENV{IDF_PATH}/tools/cmake/toolchain-esp32s3.cmake)
file(TO_CMAKE_PATH "$ENV{SENSOR_COMPILER_DIR}" SENSOR_COMPILER_DIR)
set(CMAKE_C_COMPILER "${SENSOR_COMPILER_DIR}/xtensa-esp32s3-elf-gcc.exe")
set(CMAKE_CXX_COMPILER "${SENSOR_COMPILER_DIR}/xtensa-esp32s3-elf-g++.exe")
set(CMAKE_ASM_COMPILER "${SENSOR_COMPILER_DIR}/xtensa-esp32s3-elf-gcc.exe")
