cmake_minimum_required(VERSION 3.16)
project(RestaurantSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(RestaurantSystem ${SOURCES})

target_compile_options(RestaurantSystem PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
)

include(CTest)

if(BUILD_TESTING)
    add_test(
        NAME RestaurantSystem.AllMenuOptions
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:RestaurantSystem>
            -DTEST_ROOT=${CMAKE_CURRENT_BINARY_DIR}/restaurant-system-test-cash
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/AllMenuOptions.cmake
    )
    add_test(
        NAME RestaurantSystem.CardPayment
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:RestaurantSystem>
            -DTEST_ROOT=${CMAKE_CURRENT_BINARY_DIR}/restaurant-system-test-card
            -DSCENARIO=CardPayment
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/AllMenuOptions.cmake
    )
endif()
