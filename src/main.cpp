#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;


int main(int argc, char** argv)
{
 //   ResourceManager resourcemanager(argv[0]);

// OpenGL init
    if (!glfwInit()) //glfw init
        return -1;
    // OpenGL current version print
    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;


#pragma region Window_Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#pragma endregion Window_Hints



    GLFWwindow* window;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) //glad init
    {
        std::cout << "error while glad inizialization" << std::endl;
        return -1;
    }


    glfwSetKeyCallback(window, key_callback); //Set_CallBack


    // Windowbuffer and ViewPort setting
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);



#pragma region Shaders
    GLchar* vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}";


    GLchar* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(0.9f, 0.9f, 0.4f, 1.0f);\n"
        "}\n";

#pragma endregion Shaders

#pragma region ShaderProgram_Compiling

    std::string vertexShader(vertexShaderSource);
    std::string fragmentShader(fragmentShaderSource);
    Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.IsCompiled())
    {
        std::cerr << "Can't create shader program!" << std::endl;
        return -1;
    }

#pragma endregion ShaderProgram_Compiling

#pragma region Coordinates&Indexes&colors
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

     GLfloat vertices[] = {
        -1.0f,  0.0f, 0.0f,  // Top Right
        -0.5f,  1.0f, 0.0f,  // Bottom Right
         0.0f,  0.0f, 0.0f,  // Bottom Left
         0.5f,  1.0f, 0.0f,  // Top Left
         1.0f,  0.0f, 0.0f 
    };
     GLfloat groundVertices[] = {
         0.9f, 0.9f, 0.0f,
         0.9f, 0.0f, 0.0f,
         0.4f, 0.0f, 0.0f,
         0.4f, 0.9f, 0.0f
     };


     GLfloat triangleVertices[] = {
         -1.0f, -1.0f, 0.0f,
         -0.5f, 0.0f, 0.0f,
          0.0f, -1.0f, 0.0f
     };


    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,
        3, 1, 2
    };


    
#pragma endregion Coordinates&Indexes&colors

    //Objects
    GLuint VBO, VAO, EBO;

    //Buffers Generating
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO); //VAO bind

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO bind
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW); //Data to buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //EBO bind
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Indexes to buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO unbind
    glBindVertexArray(0); // VAO unbind



    GLuint SecondVBO, SecondVAO;
    glGenBuffers(2, &SecondVBO);
    glGenVertexArrays(2, &SecondVAO);

    glBindBuffer(GL_ARRAY_BUFFER, SecondVBO);
    glBindVertexArray(SecondVAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents(); // Check for events

     // Render
      
        // Clear the colorbuffer
        glClearColor(0.5f, 0.0f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw elements
        shaderProgram.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_QUADS, 0, 4);
        glBindVertexArray(0);

        glBindVertexArray(SecondVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the screen buffers
        glfwSwapBuffers(window);

    }
    // Delete buffers, Terminate glfw (clear resurses)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}