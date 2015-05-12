#include "main.hpp"

int main()
{
    GLFWwindow *window = nullptr;
    std::string title("Hello, Triangle");
    
    enum {num_vertices = 9};
    GLfloat *vertices = new GLfloat[num_vertices]{
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    // initializes GLFW
    if (!glfwInit ())
    {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        std::exit (EXIT_FAILURE);
    }
    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow (640, 480, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent (window);

    if (!window)
    {
        std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate ();
        std::exit (EXIT_FAILURE);
    }
    
    // initializes GLEW
    glewExperimental = GL_TRUE;
    if (glewInit () != GLEW_OK)
    {
        std::cerr << "ERROR: could not start GLEW" << std::endl;
        std::exit (EXIT_FAILURE);
    }
 
    // shows renderer and version 
    const GLubyte *renderer;
    const GLubyte *version;
    renderer = glGetString (GL_RENDERER);
    version  = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    // creates VAO
    enum {Triangles, num_vaos};
    GLuint *vaos = new GLuint[num_vaos];
    enum {vPosition = 0};
    glGenVertexArrays (num_vaos, vaos);
    glBindVertexArray (vaos[Triangles]);

    // creates VBO
    enum {Buffer1, num_vbos};
    GLuint *vbos = new GLuint[num_vbos];
    glGenBuffers (num_vbos, &vbos[Buffer1]);
    glBindBuffer (GL_ARRAY_BUFFER, vbos[Buffer1]);
    glBufferData (GL_ARRAY_BUFFER, sizeof (GLfloat) * num_vertices, 
                  vertices, GL_STATIC_DRAW);

    // attaches shaders
    Shader shader("shaders/base.vert", "shaders/base.frag");

    glVertexAttribPointer (vPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray (vPosition);

    while (!glfwWindowShouldClose (window))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use ();
        glBindVertexArray (vaos[Triangles]);
        glDrawArrays (GL_TRIANGLES, 0, 3);
        glfwPollEvents ();
        glfwSwapBuffers (window);
    }

    // clears memory
    glDeleteBuffers (num_vbos, vbos);
    glDeleteVertexArrays (num_vaos, vaos);
    glBindVertexArray (0);
    glfwTerminate ();
    delete[] vaos;
    delete[] vbos;
    delete[] vertices;
    std::exit (EXIT_SUCCESS);
}
