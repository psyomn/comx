# comx

Simple comic book viewer.

# Dependencies

On your system you should have:

    libzip

comx will build these by itself in a sandbox:

    libzippp

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
