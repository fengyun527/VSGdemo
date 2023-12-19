add_executable(vsgTextures vsgTextures.cpp)

target_link_libraries(vsgTextures vsg::vsg vsgXchange::vsgXchange)

target_include_directories(vsgTextures PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS vsgTextures RUNTIME DESTINATION bin)
