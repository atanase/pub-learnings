#include "main.hpp"

int main()
{
    GLFWwindow *window = nullptr;
    
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

    window = glfwCreateWindow (640, 480, "Hello Triangle", nullptr, nullptr);
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
    std::cout << "OpenGL version supported " << version << std::endl;

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    // creates VAO
    enum VAO_IDs {Triangles, NumVAOs};
    GLuint *vaos = new GLuint[NumVAOs];
    glGenVertexArrays (NumVAOs, vaos);
    glBindVertexArray (vaos[Triangles]);
    glEnableVertexAttribArray(0);

    // creates VBO
    enum VBO_IDs {Buffer1, NumVBOs};
    GLuint *vbos = new GLuint[NumVBOs];
    glGenBuffers (NumVBOs, &vbos[Buffer1]);
    glBindBuffer (GL_ARRAY_BUFFER, vbos[Buffer1]);
    glBufferData (GL_ARRAY_BUFFER, 
                  sizeof (GLfloat) * num_vertices, 
                  vertices, 
                  GL_STATIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // attaches shaders
    Shader shader("shaders/base.vert", "shaders/base.frag");

    while (!glfwWindowShouldClose (window))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use ();
        glBindVertexArray (vaos[Triangles]);
        glDrawArrays (GL_TRIANGLES, 0, 3);
        glfwPollEvents ();
        glfwSwapBuffers (window);
        glBindVertexArray (0);
    }
    
    glfwTerminate ();
    glEnableVertexAttribArray (0);
    glBindVertexArray (0);
    delete [] vaos;
    delete [] vbos;
    delete [] vertices;
    std::exit (EXIT_SUCCESS);
}
