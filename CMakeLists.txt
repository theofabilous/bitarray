cmake_minimum_required(VERSION 3.21)
project(bitarray C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)


include_directories(
        src
        /usr/local/include
)


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
endforeach()

add_subdirectory(src/parse)
add_executable(tokenize_test tests/tokenize_test.c)
target_link_libraries(tokenize_test PUBLIC 
        parse)
target_include_directories(tokenize_test PUBLIC
        src/parse/src)


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
