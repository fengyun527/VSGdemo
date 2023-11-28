set(SOURCES
    vsgWindow.cpp
)

add_executable(vsgWindow ${SOURCES})

target_link_libraries(vsgWindow vsg::vsg)

install(TARGETS vsgWindow RUNTIME DESTINATION bin)
