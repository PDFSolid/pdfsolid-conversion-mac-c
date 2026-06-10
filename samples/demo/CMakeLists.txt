cmake_minimum_required(VERSION 3.12)

project(
        demo
        VERSION 4.1.0
        LANGUAGES C
)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(PDFSOLID_CONVERSION_SDK_VERSION ${PROJECT_VERSION})

include_directories(${CMAKE_SOURCE_DIR}/../../include)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/demo.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/../../lib/libpdfsolidconversionsdk.dylib
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "${CMAKE_SOURCE_DIR}/../../lib"
)