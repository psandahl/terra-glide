#include "Kernel.h"
#include "Viewport.h"
#include <iostream>
#include <thread>
#include <tuple>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

GLFWwindow* createGLContext(const Viewport& initialViewport);
void kernelThreadEntry(GLFWwindow* window);
void applicationThreadEntry();

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

    // Start the application thread.
    std::thread applicationThread(applicationThreadEntry);

    // Continue the kernel thread in the current thread.
    kernelThreadEntry(window);

    // Wait for the application thread.
    applicationThread.join();

    // Close OpenGL.
    glfwTerminate();

    // Done with successful status.
    return 0;
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

void kernelThreadEntry(GLFWwindow* window)
{
    // Dummy for now.
    glViewport(0, 0, 1024, 768);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void applicationThreadEntry()
{
}