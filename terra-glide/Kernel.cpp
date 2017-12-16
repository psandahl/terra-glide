#include "Kernel.h"
#include "TerraGlide.h"
#include "Viewport.h"
#include <iostream>
#include <memory>
#include <tuple>

GLFWwindow* createGLContext(const Viewport& initialViewport);
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

    // Let the Kernel and the TerraGlide objects live on the stack.
    TerraGlide terraGlide;
    Kernel kernel(window, initialViewport, terraGlide, glfwGetTime());

    // Set the global Kernel pointer and register callbacks.
    g_kernel = &kernel;

    // Setup TerraGlide stuff.
    if (terraGlide.setup() == TerraGlideStatus::Stop)
    {
        std::cerr << "TerraGlide: Application setup failed.\n";
        glfwTerminate();
        return -1;
    }

    // Set the window size callback.
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    // Run the render loop.
    kernel.renderLoop();

    // Teardown the TerraGlide.
    terraGlide.teardown();

    // Close OpenGL.
    glfwTerminate();

    // Done with successful status.
    return 0;
}

void Kernel::renderLoop() noexcept
{
    while (!glfwWindowShouldClose(m_window))
    {
        auto now = glfwGetTime();
        auto frameDuration = now - m_lastTimestamp;
        m_lastTimestamp = now;

        if (m_terraGlide.frame(m_viewport, now) == TerraGlideStatus::Stop)
        {
            break;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
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

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Callback. New size: " << width << ", " << height << std::endl;
    g_kernel->setViewport(width, height);
}