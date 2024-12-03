cmake_minimum_required(VERSION 3.10)
project(lr7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(lr7_exe main.cpp src/bear.cpp src/npc.cpp src/outlaw.cpp src/werewolf.cpp include/bear.hpp include/npc.hpp include/observer.hpp include/outlaw.hpp include/werewolf.hpp)

target_include_directories(lr7_exe PRIVATE include)

# # Добавление тестов
# enable_testing()

# add_executable(tests test/lrTests.cpp)
# target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

# # Добавление тестов в тестовый набор
# add_test(NAME MyProjectTests COMMAND tests)