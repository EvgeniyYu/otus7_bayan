cmake_minimum_required(VERSION 3.2)

set(SRC ./src/cmd_line_processor.cpp ./src/file_comparator.cpp ./src/file_scanner.cpp ./src/file_validator.cpp ./src/hash_algorithm.cpp)
set(PATHS include/)
set(NAME_EXECUTABLE "bayan")
set(NAME_TEST "test_bayan")


if ($ENV{GITHUB_RUN_NUMBER})
	project(${NAME_EXECUTABLE} VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
	project(${NAME_EXECUTABLE} VERSION 0.0.1)
endif()


find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)

add_executable(${NAME_EXECUTABLE} ${SRC} ./src/main.cpp)

add_executable(${NAME_TEST} ${SRC} ./src/test.cpp)

set_target_properties(${NAME_EXECUTABLE} ${NAME_TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(${NAME_TEST} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(${NAME_EXECUTABLE} 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(${NAME_EXECUTABLE} 
    PRIVATE "${PATHS}"
)

target_include_directories(${NAME_TEST} 
    PRIVATE "${PATHS}"
)


target_include_directories(${NAME_TEST} 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${NAME_EXECUTABLE} PUBLIC ${Boost_LIBRARIES})

target_link_libraries(${NAME_TEST}
    ${Boost_LIBRARIES}
)

if (MSVC)
    target_compile_options(${NAME_EXECUTABLE} PRIVATE
        /W4
    )
    target_compile_options(${NAME_TEST} PRIVATE
        /W4
    )
else ()
    target_compile_options(${NAME_EXECUTABLE} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${NAME_TEST} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()



install(TARGETS ${NAME_EXECUTABLE} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT evgeniy.yurevich@gmail.com)

include(CPack)

enable_testing()

add_test(${NAME_TEST} ${NAME_TEST})
