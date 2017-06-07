cmake_minimum_required(VERSION 3.6)
project(tig)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/tig.cpp src/diff.cpp src/diff.h src/init.cpp src/init.h src/common.cpp src/common.h src/status.cpp src/status.h src/add.cpp src/add.h src/checkout.cpp src/checkout.h src/reset.cpp src/reset.h src/clone.cpp src/clone.h src/config.cpp src/config.h src/commit.cpp src/commit.h src/push.cpp src/push.h src/pull.cpp src/pull.h src/log.cpp src/log.h src/help.cpp src/help.h)
add_executable(tig ${SOURCE_FILES})