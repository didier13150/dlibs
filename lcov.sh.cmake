#!/bin/bash

# Clean up
make clean
rm -rf CMakeFiles src Testing tests

find . -name '*.info' -delete
rm -rf ../lcov/??*

# Reset lcov
lcov --zerocounters --directory @CMAKE_SOURCE_DIR@

# Build project
cmake -DWITH_LCOV=ON -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

# Init lcov
lcov --no-external --follow --capture --initial --directory @CMAKE_SOURCE_DIR@ --output-file base.info

# Run test
make -k test

# lcov
lcov --no-external --follow --capture --directory @CMAKE_SOURCE_DIR@ --output-file test.info
lcov --add-tracefile base.info --add-tracefile test.info --output-file total.info

lcov --remove total.info '/usr/include/*' '/usr/lib*/*' 'src/sqlite3.*' 'src/dlibspath.cpp' --output-file filtered.info

genhtml --ignore-errors source filtered.info --legend --title "DLibs libraries @DLIBS_VERSION@" --output-directory=@CMAKE_SOURCE_DIR@/lcov
