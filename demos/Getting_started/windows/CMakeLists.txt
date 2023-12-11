set(SOURCES
    vsgWindows.cpp
)

add_executable(vsgWindows ${SOURCES})

target_link_libraries(vsgWindows vsg::vsg)

install(TARGETS vsgWindows RUNTIME DESTINATION bin)
