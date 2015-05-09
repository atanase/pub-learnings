#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

int main() {
    GLFWwindow *window = nullptr;
    const GLubyte *renderer;
    const GLubyte *version;
    GLuint vao;
    GLuint vbo;

    GLfloat points[] = {
         0.0f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    const char *vertex_shader =
        "#version 410\n"
        "in vec3 vp;"
        "void main () {"
        "    gl_Position = vec4(vp, 1.0);"
        "}";
    
    const char *fragment_shader =
        "#version 410\n"
        "out vec4 frag_color;"
        "void main () {"
        "    frag_color = vec4(0.5, 0.0, 0.5, 1.0);"
        "}";
    GLuint vs, fs;
    GLuint shader_programme;
    
    if (!glfwInit ()) {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        return EXIT_FAILURE;
    }
    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow (640, 480, "Hello Triangle", nullptr, nullptr);
    glfwMakeContextCurrent (window);
    if (!window) {
        std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate ();
        return EXIT_FAILURE;
    }
    
    glewExperimental = GL_TRUE;
    glewInit ();
    
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

    vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, nullptr);
    glCompileShader (vs);
    fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, nullptr);
    glCompileShader (fs);
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    while (!glfwWindowShouldClose (window) ) {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (shader_programme);
        glBindVertexArray (vao);
        glDrawArrays (GL_TRIANGLES, 0, 3);
        glfwPollEvents ();
        glfwSwapBuffers (window);
    }
    glfwTerminate ();
    return EXIT_SUCCESS;
}
