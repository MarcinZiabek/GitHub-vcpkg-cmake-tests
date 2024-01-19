# configure CMAKE
cmake_minimum_required(VERSION 3.27)
project(questpdf_library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE MinSizeRel)
add_compile_options(-O3)


# enable IPO to achieve better performance, reduce artifact size
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO is not supported: ${output}")
endif()


# include all code source files
file(GLOB_RECURSE SOURCES "src/*.cpp")


# select between running as application (main.cpp) or producing the library
add_library(skia_questpdf SHARED ${SOURCES})
#add_executable(skia_questpdf ${SOURCES})


# configure output file name
set_target_properties(skia_questpdf PROPERTIES OUTPUT_NAME "skia_questpdf" PREFIX "")


# configure VCPKG and install packages
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
find_package(unofficial-skia REQUIRED)
target_link_libraries(skia_questpdf PRIVATE unofficial::skia::skia unofficial::skia::modules::skparagraph unofficial::skia::modules::svg)

# reduce output package size
add_custom_command(TARGET skia_questpdf POST_BUILD COMMAND ${CMAKE_STRIP} -x $<TARGET_FILE:skia_questpdf>)
