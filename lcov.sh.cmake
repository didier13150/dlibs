#!/bin/bash

OUTPUT_DIR="@CMAKE_SOURCE_DIR@"

# Clean up
make clean
find . -name '*.info' -delete
rm -rf ../lcov/??*

# Reset lcov
lcov --zerocounters --directory ${OUTPUT_DIR}

# Build project
cmake -DWITH_LCOV=ON -DCMAKE_BUILD_TYPE=Debug ..
make

# Init lcov
lcov --no-external --capture --initial --directory ${OUTPUT_DIR} --output-file base.info

# Run test
make -k test

# lcov
lcov --no-external --capture --directory ${OUTPUT_DIR} --output-file test.info
lcov --add-tracefile base.info --add-tracefile test.info --output-file total.info
lcov --remove total.info '/usr/include/*' '/usr/lib/*' 'src/sqlite3.*' --output-file filtered.info
#cp total.info filtered.info

genhtml --ignore-errors source filtered.info --legend --title "DLibs libraries" --output-directory=${OUTPUT_DIR}/lcov
