#include <iostream>
#include <cstdlib>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Shader.hpp"



int main()
{
    GLFWwindow *window = nullptr;

    GLuint vao;
    GLuint vbo;

	GLfloat points[] = {
         0.0f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         -0.5f, -0.5f,  0.0f
    };

    // GLFW initialization
    if (!glfwInit ())
    {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        std::exit (EXIT_FAILURE);
    }
    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow (640, 480, "Hello Triangle", nullptr, nullptr);
    glfwMakeContextCurrent (window);

    if (!window)
    {
        std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate ();
        std::exit (EXIT_FAILURE);
    }
    
    // GLEW initialization
    glewExperimental = GL_TRUE;
    if (glewInit () != GLEW_OK)
    {
        std::cerr << "ERROR: could not start GLEW" << std::endl;
        std::exit (EXIT_FAILURE);
    }
 
    // output: renderer and version 
    const GLubyte *renderer;
    const GLubyte *version;
    renderer = glGetString (GL_RENDERER);
    version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    // attach shaders
    Shader shader("shaders/base.vert", "shaders/base.frag");

    while (!glfwWindowShouldClose (window))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use ();
        glBindVertexArray (vao);
        glDrawArrays (GL_TRIANGLES, 0, 3);
        glfwPollEvents ();
        glfwSwapBuffers (window);
    }
    
    glfwTerminate ();
    std::exit (EXIT_SUCCESS);
}
