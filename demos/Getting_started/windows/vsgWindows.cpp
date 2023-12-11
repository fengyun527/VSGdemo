#include <vsg/all.h>

int main(int argc, char** argv)
{
    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = "vsgwindow";

    if (arguments.read({ "--window", "-w" }, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }

    auto viewer = vsg::Viewer::create();
    auto window = vsg::Window::create(windowTraits);

    auto windowTraints1 = vsg::WindowTraits::create();
    windowTraints1->device = window->getOrCreateDevice();
    windowTraints1->x = 100; // diffrent from window
    windowTraints1->y = 100; // diffrent from window

    auto window1 = vsg::Window::create(windowTraints1);

    auto commandGraph = vsg::CommandGraph::create(window);
    auto commandGraph1 = vsg::CommandGraph::create(window1);

    viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph, commandGraph1});

    // add close handler to respond to the close window button and pressing escape
    // viewer->addEventHandler(vsg::CloseHandler::create(viewer));

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
