cmake_minimum_required(VERSION 3.21)
project(bitarray C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-nullability-completeness")

find_package(Curses REQUIRED)


add_custom_target(makeperf ALL DEPENDS dummy)

add_custom_command(OUTPUT dummy
        COMMAND echo Rebuilding perfect hash
        COMMAND python ../src/parse/makeperf.py
        COMMAND gperf -L C -t -G ../src/parse/tokens.gperf --output-file=../src/parse/tokenhash.h
        DEPENDS always_rebuild)

add_custom_command(OUTPUT always_rebuild
        COMMAND cmake -E echo)


if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
        if(NOT DEFINED MACOSX_SDK_PATH)
                execute_process(
                        COMMAND xcrun --show-sdk-path
                        OUTPUT_VARIABLE MACOSX_SDK_PATH
                )
                string(STRIP ${MACOSX_SDK_PATH} MACOSX_SDK_PATH)
        endif()
        include_directories(
                SYSTEM ${MACOSX_SDK_PATH}/usr/include
        )
endif()

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

target_compile_options(bitarray PUBLIC
        -Wno-format)

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
                -Wno-format)
endforeach()


add_subdirectory(src/parse)
add_executable(tokenize_test tests/tokenize_test.c)
target_link_libraries(tokenize_test PUBLIC 
        parse)
target_include_directories(tokenize_test PUBLIC
        src/parse)



add_executable(binav
        examples/binav.c
)

target_include_directories(binav
        PUBLIC /Applications/VLC.app/Contents/MacOS/include
        PUBLIC /Library/Frameworks/SDL2.framework/Versions/A/Headers/
)

target_link_libraries(binav
        bitarray
        "-framework CoreFoundation"
        "-framework Security"
        "-framework VideoToolbox"
        "-framework CoreMedia"
        "-framework CoreVideo"
        "-undefined dynamic_lookup"
        avcodec
        avformat
        avfilter
        avdevice
        swresample
        swscale
        avutil
        sdl2
        ${CURSES_LIBRARIES}
        "-undefined dynamic_lookup"
)
