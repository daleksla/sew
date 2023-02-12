cmake_minimum_required(VERSION 3.12)

### Project name and a few useful settings. Other commands can pick up the results ###
project(
  razan
  DESCRIPTION "SEW (Salih's Encryption Wrapper) is a wrapper around openssl's encryption functionality, allowing for simpler encryption for basic communications"
  LANGUAGES C CXX
  VERSION 1.0
)

### Set where CMake will output files ###
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


### Configure relevant toolchains used to compile ###
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic -g -Wall -fPIC -fno-exceptions)
add_compile_definitions(OPENSSL_PIC SEW_MODULUS_P=23 SEW_BASE_G=5)
set(LINK_LIBRARIES "/usr/local/lib64/libcrypto.a -lm -lstdc++ -lssl -lcrypto -lz")
include_directories(
	/usr/include/openssl
	include/
)

### Configure any related projects commands (e.g. creating documentation) ###
#find_package(Doxygen)
#if(Doxygen_FOUND)
#  execute_process(COMMAND doxygen .config.txt)
#else()
#  message(STATUS "Doxygen tool not found, not building additional source code docs")
#endif()


### Now actually compile ###
add_library(sew src/key_generation.c src/key_exchange.c src/encryption.c)
