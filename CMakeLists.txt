cmake_minimum_required(VERSION 3.21)
project(bitarray C)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 11)
set(LLVM_EXTERNALIZE_DEBUGINFO ON)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-nullability-completeness ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wno-nullability-completeness ")
# set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
# set(CMAKE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")

find_package(Curses REQUIRED)

message(STATUS "COMPILER: ${CMAKE_C_COMPILER_ID}")

# set(CMAKE_VERBOSE_MAKEFILE ON)

add_custom_target(makeperf ALL DEPENDS dummy)

add_custom_command(OUTPUT dummy
        WORKING_DIRECTORY ../src/parse
        COMMAND echo Rebuilding perfect hash...
        COMMAND python makeperf.py
        COMMAND echo Done rebuilding perfect hash
        DEPENDS always_rebuild)

add_custom_command(OUTPUT always_rebuild
        COMMAND cmake -E echo)


# if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
#         if(NOT DEFINED MACOSX_SDK_PATH)
#                 execute_process(
#                         COMMAND xcrun --show-sdk-path
#                         OUTPUT_VARIABLE MACOSX_SDK_PATH
#                 )
#                 string(STRIP ${MACOSX_SDK_PATH} MACOSX_SDK_PATH)
#         endif()
#         include_directories(
#                 SYSTEM ${MACOSX_SDK_PATH}/usr/include
#         )
# endif()

include_directories(
        src
        /usr/local/include)

link_directories(
        /usr/local/lib
)


add_library(bitarray STATIC
        src/util/bit_util.c
        src/bitarray.c
        src/bitbuffer.c
        src/bitunpack.c
        src/binarymap.c
        # src/binunpack.c
)

# target_compile_options(bitarray PUBLIC
        # -Wno-format -O2)

target_compile_options(bitarray PUBLIC
        # -Wno-format -O0 -g)
        # -Wno-format -O3 -g -fno-inline)
        -Wno-format -O3 -g)
        # -Wno-format -O2 -g)
        # -Wno-format -O1 -g)

add_executable(buffer_examples
        examples/buffer_examples.c
)

target_link_libraries(buffer_examples
        bitarray
)

list(APPEND TestTargets 
        main_tests
        module_tests 
        file_tests
        # tokenize_tests
        )
list(APPEND TestFiles 
        bitarray_test 
        bitarray_module_tests 
        file_tests
        # tokenize_test
        )

foreach(target file IN ZIP_LISTS TestTargets TestFiles)
        add_executable(
                ${target}
                tests/${file}.c
        )
        target_link_libraries(
                ${target}
                bitarray
        )
        target_compile_options(${target} PUBLIC
                # -Wno-format -g)
                -Wno-format -O3 -g)
endforeach()


add_subdirectory(src/parse)
add_executable(tokenize_test tests/tokenize_test.c)
target_link_libraries(tokenize_test PUBLIC 
        parse)
target_include_directories(tokenize_test PUBLIC
        src/parse)



# add_executable(binav
#         examples/binav.c
# )
#
# target_include_directories(binav
# 		PUBLIC /usr/local/include/SDL2
# )
#
# target_link_libraries(binav
#         bitarray
#         "-framework CoreFoundation"
#         "-framework Security"
#         "-framework VideoToolbox"
#         "-framework CoreMedia"
#         "-framework CoreVideo"
#         "-undefined dynamic_lookup"
#         avcodec
#         avformat
#         avfilter
#         avdevice
#         swresample
#         swscale
#         avutil
#         sdl2
#         ${CURSES_LIBRARIES}
#         "-undefined dynamic_lookup"
# )
