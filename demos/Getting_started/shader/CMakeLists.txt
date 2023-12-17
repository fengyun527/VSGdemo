add_executable(vsgPushConstant vsgPushConstant.cpp)

target_link_libraries(vsgPushConstant vsg::vsg)

install(TARGETS vsgPushConstant RUNTIME DESTINATION bin)
