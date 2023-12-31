#include <vsg/all.h>

#include <iostream>

std::string vertexShaderSource{R"(
#version 450
layout(location = 0) in vec3 vsg_Vertex;
layout(location = 1) in vec3 vsg_Color;

layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = vec4(vsg_Color, 1.0f);
    gl_Position = vec4(vsg_Vertex, 1.0f);
})"
};
std::string fragmentShaderSource{R"(
#version 450
layout(location = 0) in vec4 fragColor;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = fragColor;
})"
};

int main(int argc, char** argv)
{
    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "vsgTriangle";

    if (arguments.read({ "--window", "-w" }, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }

    vsg::ref_ptr<vsg::ShaderStage> vertexShader = vsg::ShaderStage::create(VK_SHADER_STAGE_VERTEX_BIT, "main", vertexShaderSource);
    vsg::ref_ptr<vsg::ShaderStage> fragmentShader = vsg::ShaderStage::create(VK_SHADER_STAGE_FRAGMENT_BIT, "main", fragmentShaderSource);
    if (!vertexShader || !fragmentShader)
    {
        std::cout << "Could not create shaders." << std::endl;
        return 1;
    }

    vsg::VertexInputState::Bindings vertexBindingsDescriptions{
        VkVertexInputBindingDescription{0, 6 * sizeof(float), VK_VERTEX_INPUT_RATE_VERTEX}, // vertex data
    };

    vsg::VertexInputState::Attributes vertexAttributeDescriptions{
        VkVertexInputAttributeDescription{0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0}, // vertex data
        VkVertexInputAttributeDescription{1, 0, VK_FORMAT_R32G32B32_SFLOAT, 3 * sizeof(float)}, // vertex data
    };

    // I use data from learnOpengl - hello Triangle, the triangl direction is not point out of the screen because of different NDC in vulkan
    auto rasterization = vsg::RasterizationState::create();
    rasterization->cullMode = VK_CULL_MODE_NONE;

    vsg::GraphicsPipelineStates pipelineStates{
        vsg::VertexInputState::create(vertexBindingsDescriptions, vertexAttributeDescriptions),
        vsg::InputAssemblyState::create(),
        rasterization,
        vsg::MultisampleState::create(),
        vsg::ColorBlendState::create(), 
        vsg::DepthStencilState::create()
    };

    auto pipelineLayout = vsg::PipelineLayout::create();
    auto graphicsPipeline = vsg::GraphicsPipeline::create(pipelineLayout, vsg::ShaderStages{ vertexShader, fragmentShader }, pipelineStates);
    auto bindGraphicsPipeline = vsg::BindGraphicsPipeline::create(graphicsPipeline);

    // create StateGroup as the root of the scene/command graph to hold the GraphicsPipeline
    auto scenegraph = vsg::StateGroup::create();
    scenegraph->add(bindGraphicsPipeline);

    auto verticesData = vsg::floatArray::create({
        // positions         // colors
         0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top 
        });
    // setup geometry
    auto drawCommands = vsg::Commands::create();
    drawCommands->addChild(vsg::BindVertexBuffers::create(0, vsg::DataList{ verticesData }));
    drawCommands->addChild(vsg::Draw::create(3, 1, 0, 0));

    scenegraph->addChild(drawCommands);

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    auto window = vsg::Window::create(windowTraits);
    if (!window)
    {
        std::cout << "Could not create window." << std::endl;
        return 1;
    }

    viewer->addWindow(window);

    auto camera = vsg::Camera::create();

    auto commandGraph = vsg::createCommandGraphForView(window, camera, scenegraph);
    viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph });

    // compile the Vulkan objects
    viewer->compile();

    // assign a CloseHandler to the Viewer to respond to pressing Escape or the window close button
    viewer->addEventHandlers({ vsg::CloseHandler::create(viewer) });

    viewer->compile();

    while (viewer->advanceToNextFrame())
    {
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }

    // clean up done automatically thanks to ref_ptr<>
    return 0;
}
