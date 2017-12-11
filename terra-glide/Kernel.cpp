#include "Event.h"
#include "Kernel.h"
#include "Link.h"
#include "Request.h"
#include "TerraGlide.h"
#include "Viewport.h"
#include <iostream>
#include <memory>
#include <thread>
#include <tuple>

GLFWwindow* createGLContext(const Viewport& initialViewport);
void kernelThreadEntry(std::shared_ptr<Kernel> kernel);
void applicationThreadEntry(std::shared_ptr<TerraGlide> terraGlide);
void windowSizeCallback(GLFWwindow* window, int width, int height);

// In order to handle callbacks we must have a plain old pointer. But
// don't worry, once set if will never change to any other object.
Kernel* g_kernel = nullptr;

int runTerraGlide(Viewport initialViewport)
{
    // Create the OpenGL context.
    GLFWwindow* window = createGLContext(initialViewport);
    if (!window)
    {
        // Error message shall have been written by createGLContext.
        return -1;
    }

    // Initialize function pointers through GLAD.
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "TerraGlide: Cannot initialize GLAD.\n";
        glfwTerminate();
        return -1;
    }

    // Create the Events link.
    auto events = std::make_shared<Link<Event>>();

    // Create the StopRequests link.
    auto stopRequests = std::make_shared<Link<StopRequest>>();

    // Let the Kernel and the TerraGlide objects live on the heap.
    auto kernel = std::make_shared<Kernel>(window, events, stopRequests, 
                                           initialViewport, glfwGetTime());
    auto terraGlide = std::make_shared<TerraGlide>(events, stopRequests);

    // Set the global Kernel pointer and register callbacks.
    g_kernel = kernel.get();

    // Set the window size callback.
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    // Start the application thread.
    std::thread applicationThread(applicationThreadEntry, terraGlide);

    // Continue the kernel thread in the current thread.
    kernelThreadEntry(kernel);

    // Wait for the application thread.
    applicationThread.join();

    // Close OpenGL.
    glfwTerminate();

    // Done with successful status.
    return 0;
}

void Kernel::applyGlobalSettings() const noexcept
{
    // Dummy for now.
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Kernel::renderLoop() noexcept
{
    while (!glfwWindowShouldClose(m_window))
    {
        scanRequests();

        auto[width, height] = m_viewport;
        auto now = glfwGetTime();
        auto frameDuration = now - m_lastTimestamp;
        m_lastTimestamp = now;

        m_events->post({ EventType::Frame, { frameDuration, width, height } });

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    // If the termination is initiated by TerraGlide this is
    // unnecessary, but it's harmless. Keep it simple.
    m_events->post({ EventType::Quit });
}

void Kernel::scanRequests() noexcept
{
    auto shallStop = m_stopRequests->poll();
    if (shallStop.has_value())
    {
        // Signal GLFW for termination.
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

// Create and configure the OpenGL context. The context is made
// current (bound to the current thread) if the function is
// successful. If the function is unsuccessful termination
// is made.
GLFWwindow* createGLContext(const Viewport& initialViewport)
{
    if (!glfwInit())
    {
        std::cerr << "TerraGlide: Cannot create an OpenGL context.\n";
        return nullptr;
    }

    // Setting window hints.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Try creating a window.
    auto window = glfwCreateWindow(std::get<0>(initialViewport), 
                                   std::get<1>(initialViewport),
                                   "TerraGlide", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "TerraGlide: Cannot create an OpenGL window.\n";
        glfwTerminate();
        return nullptr;
    }

    // Successful!
    glfwMakeContextCurrent(window);
    return window;
}

void kernelThreadEntry(std::shared_ptr<Kernel> kernel)
{
    kernel->applyGlobalSettings();
    kernel->renderLoop();
}

void applicationThreadEntry(std::shared_ptr<TerraGlide> terraGlide)
{
    terraGlide->run();
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Callback. New size: " << width << ", " << height << std::endl;
    g_kernel->setViewport(width, height);
}