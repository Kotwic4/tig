cmake_minimum_required(VERSION 3.6)
project(tig)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/tig.cpp src/util/diff.cpp src/util/diff.h src/util/init.cpp src/util/init.h src/util/common.cpp src/util/common.h src/util/status.cpp src/util/status.h src/commit/add.cpp src/commit/add.h src/commit/checkout.cpp src/commit/checkout.h src/commit/reset.cpp src/commit/reset.h src/web/clone.cpp src/web/clone.h src/util/config.cpp src/util/config.h src/commit/commit.cpp src/commit/commit.h src/web/push.cpp src/web/push.h src/web/pull.cpp src/web/pull.h src/commit/log.cpp src/commit/log.h src/util/help.cpp src/util/help.h src/web/server.cpp src/web/server.h src/web/web.cpp src/web/web.h src/web/client.cpp src/web/client.h)
add_executable(tig ${SOURCE_FILES})