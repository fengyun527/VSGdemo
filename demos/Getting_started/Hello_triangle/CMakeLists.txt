add_executable(vsgTriangle vsgTriangle.cpp)

target_link_libraries(vsgTriangle vsg::vsg)

add_executable(vsgTriangle_indexed vsgTriangle_indexed.cpp)

target_link_libraries(vsgTriangle_indexed vsg::vsg)

install(TARGETS vsgTriangle vsgTriangle_indexed RUNTIME DESTINATION bin)
