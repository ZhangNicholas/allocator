cmake_minimum_required(VERSION 3.5)

if($ENV{TRAVIS_BUILD_NUMBER})
	project(myAllocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
	project(myAllocator VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)

# Lookup for pre-built gtest
#find_package(GTest REQUIRED)

set(SOURCES src/main.cpp
	src/Allocator.cpp
	src/PoolAllocator
	src/Benchmark.cpp
)

# Main target
add_executable(myAllocator ${SOURCES})

# Test target
#[[add_executable(
	test_myAllocator
	"test/test_my_allocator.cpp"
)]]

set_target_properties(myAllocator #[[test_myAllocator]] PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(
	myAllocator
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

# Add googletest, src to the include directories for the test target
#target_include_directories(
#	test_myAllocator
#	PRIVATE ${GTEST_INCLUDE_DIRS}
#	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
#	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/includes"
#)

# Link test target against gtest libraries
#target_link_libraries(
#	test_myAllocator PRIVATE
#	${GTEST_BOTH_LIBRARIES}
#)

if (MSVC)
	# @see https://github.com/google/googletest/blob/master/googletest/README.md
	# Visual Studio Dynamic vs Static Runtimes
	#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

	target_compile_options(
		myAllocator PRIVATE
		/W4
	)
	#[[target_compile_options(
		test_myAllocator PRIVATE
		/W4
	)]]
else ()
	target_compile_options(
		myAllocator PRIVATE
		-Wall -Wextra -pedantic #-Werror
	)
	#[[target_compile_options(
		test_myAllocator PRIVATE
		-Wall -Wextra -pedantic #-Werror
	)]]
endif()

install(TARGETS myAllocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cnickol@gmail.com)

include(CPack)

#enable_testing()

#add_test(test_myAllocator test_myAllocator)