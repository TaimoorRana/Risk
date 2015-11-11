set(CLI_SOURCE_FILES
	main.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/lib")

add_executable(${PROJECT_NAME}-cli ${CLI_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}-cli lib${PROJECT_NAME})
