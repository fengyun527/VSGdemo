set(SOURCES
    vsgTriangle.cpp
)

add_executable(vsgTriangle ${SOURCES})

target_link_libraries(vsgTriangle vsg::vsg)

install(TARGETS vsgTriangle RUNTIME DESTINATION bin)
