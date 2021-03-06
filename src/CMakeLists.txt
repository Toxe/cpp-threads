set(ALL_TARGETS
    nth_prime_single_threaded
    async
    atomic
    condition_variable
    lock_guard
    mutex_timer
    producer_consumer
    thread_local
    thread_class
)

add_executable(thread_local thread_local.cpp)
add_executable(nth_prime_single_threaded nth_prime_single_threaded.cpp
                                         common/prime.h common/prime.cpp)
add_executable(async async.cpp
                     common/prime.h common/prime.cpp)
add_executable(atomic atomic.cpp
                      common/prime.h common/prime.cpp)
add_executable(condition_variable condition_variable.cpp
                                  common/prime.h common/prime.cpp)
add_executable(lock_guard lock_guard.cpp
                          common/prime.h common/prime.cpp)
add_executable(mutex_timer mutex_timer.cpp
                           common/mutex_timer.h
                           common/prime.h common/prime.cpp)
add_executable(producer_consumer producer_consumer.cpp
                                 common/prime.h common/prime.cpp)
add_executable(thread_class thread_class.cpp
                            common/prime.h common/prime.cpp)

# std::jthread: GCC 10+, MSVC 19.28
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0")
    list(APPEND ALL_TARGETS jthread)

    add_executable(jthread jthread.cpp
                           common/prime.h common/prime.cpp)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.28")
    list(APPEND ALL_TARGETS jthread)

    add_executable(jthread jthread.cpp
                           common/prime.h common/prime.cpp)
endif()

# std::latch: GCC 11, Clang 11, MSVC 19.28
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0")
    list(APPEND ALL_TARGETS latch_arrive_and_wait
                            latch_wait)

    add_executable(latch_arrive_and_wait latch_arrive_and_wait.cpp
                                         common/prime.h common/prime.cpp)
    add_executable(latch_wait latch_wait.cpp
                              common/prime.h common/prime.cpp)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0")
    if(NOT APPLE)
        list(APPEND ALL_TARGETS latch_arrive_and_wait
                                latch_wait)

        add_executable(latch_arrive_and_wait latch_arrive_and_wait.cpp
                                             common/prime.h common/prime.cpp)
        add_executable(latch_wait latch_wait.cpp
                                  common/prime.h common/prime.cpp)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.28")
    list(APPEND ALL_TARGETS latch_arrive_and_wait
                            latch_wait)

    add_executable(latch_arrive_and_wait latch_arrive_and_wait.cpp
                                         common/prime.h common/prime.cpp)
    add_executable(latch_wait latch_wait.cpp
                              common/prime.h common/prime.cpp)
endif()

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
endforeach()
