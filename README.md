# comx

Simple comic book viewer.

# Dependencies

    zlib

# Build

    mkdir build
    cd build
    cmake ..
    make

You can use the generator, to use ninja if that's your thing:

    mkdir build
    cd build
    cmake .. -G Ninja
    make

# Test

    make test
    ninja test
