add_executable(main main.cpp)

target_link_libraries(main PRIVATE LJGL)

# Copy GLSL files over to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/GLSL DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy all VBO/EBO files over to the build directory
file(GLOB ASSETS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.vbo"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ebo"
)
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
