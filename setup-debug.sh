# Configure package and build debug libraries
meson setup "$@" --buildtype debug build-debug
./build-cc-debug.sh
cd python
meson setup "$@" --buildtype debug build-debug
cd ..
./build-py-debug.sh
