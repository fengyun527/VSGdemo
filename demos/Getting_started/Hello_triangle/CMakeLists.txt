add_executable(vsgTriangle vsgTriangle.cpp)

target_link_libraries(vsgTriangle vsg::vsg)

add_executable(vsgTriangle_indexed vsgTriangle_indexed.cpp)

target_link_libraries(vsgTriangle_indexed vsg::vsg)

add_executable(vsgTriangleColored vsgTriangleColored.cpp)

target_link_libraries(vsgTriangleColored vsg::vsg)

install(TARGETS vsgTriangle vsgTriangle_indexed vsgTriangleColored RUNTIME DESTINATION bin)
