#include "Kernel.h"
#include "TerraGlide.h"
#include "Viewport.h"
#include <iostream>
#include <memory>
#include <tuple>

GLFWwindow* createGLContext(const Viewport& initialViewport);
void windowSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

// In order to handle callbacks we need som plain old pointers.
Kernel* g_kernel = nullptr;
TerraGlide* g_terraGlide = nullptr;

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

    // Set the global pointers.
    g_kernel = &kernel;
    g_terraGlide = &terraGlide;

    // Setup TerraGlide stuff.
    if (terraGlide.setup() == TerraGlideStatus::Stop)
    {
        std::cerr << "TerraGlide: Application setup failed.\n";
        glfwTerminate();
        return -1;
    }

    // Register callbacks.
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Run the render loop.
    kernel.renderLoop();

    // Teardown the TerraGlide.
    terraGlide.teardown();

    // Unregister callbacks.
    glfwSetWindowSizeCallback(window, nullptr);
    glfwSetKeyCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);

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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        g_terraGlide->keyDown(key);
    }
    else if (action == GLFW_RELEASE)
    {
        g_terraGlide->keyUp(key);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        g_terraGlide->leftButtonDown(xpos, ypos);
        glfwSetCursorPosCallback(window, cursorPosCallback);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        g_terraGlide->leftButtonUp(xpos, ypos);
        glfwSetCursorPosCallback(window, nullptr);
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    g_terraGlide->cursorPos(xpos, ypos);
}