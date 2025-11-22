#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <sstream>

// Dimensione iniziale finestra
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

// Vertex shader con normali
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

// Fragment shader con luce direzionale
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    float diff = max(dot(normalize(Normal), normalize(-lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = 0.2 * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
)";

// Callback ridimensionamento
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "graphicEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Errore creazione finestra\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Errore inizializzazione GLAD\n";
        return -1;
    }

    // Cubo
    float vertices[] = {
        // posizioni           // normali
        -0.5f,-0.5f,-0.5f,  0.0f,0.0f,-1.0f,
         0.5f,-0.5f,-0.5f,  0.0f,0.0f,-1.0f,
         0.5f, 0.5f,-0.5f,  0.0f,0.0f,-1.0f,
         0.5f, 0.5f,-0.5f,  0.0f,0.0f,-1.0f,
        -0.5f, 0.5f,-0.5f,  0.0f,0.0f,-1.0f,
        -0.5f,-0.5f,-0.5f,  0.0f,0.0f,-1.0f,

        -0.5f,-0.5f, 0.5f,  0.0f,0.0f,1.0f,
         0.5f,-0.5f, 0.5f,  0.0f,0.0f,1.0f,
         0.5f, 0.5f, 0.5f,  0.0f,0.0f,1.0f,
         0.5f, 0.5f, 0.5f,  0.0f,0.0f,1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f,0.0f,1.0f,
        -0.5f,-0.5f, 0.5f,  0.0f,0.0f,1.0f,

        -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f,
        -0.5f, 0.5f,-0.5f, -1.0f,0.0f,0.0f,
        -0.5f,-0.5f,-0.5f, -1.0f,0.0f,0.0f,
        -0.5f,-0.5f,-0.5f, -1.0f,0.0f,0.0f,
        -0.5f,-0.5f, 0.5f, -1.0f,0.0f,0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f,

         0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f,
         0.5f, 0.5f,-0.5f, 1.0f,0.0f,0.0f,
         0.5f,-0.5f,-0.5f, 1.0f,0.0f,0.0f,
         0.5f,-0.5f,-0.5f, 1.0f,0.0f,0.0f,
         0.5f,-0.5f, 0.5f, 1.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f,

        -0.5f,-0.5f,-0.5f, 0.0f,-1.0f,0.0f,
         0.5f,-0.5f,-0.5f, 0.0f,-1.0f,0.0f,
         0.5f,-0.5f, 0.5f, 0.0f,-1.0f,0.0f,
         0.5f,-0.5f, 0.5f, 0.0f,-1.0f,0.0f,
        -0.5f,-0.5f, 0.5f, 0.0f,-1.0f,0.0f,
        -0.5f,-0.5f,-0.5f, 0.0f,-1.0f,0.0f,

        -0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f,
         0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f,
         0.5f, 0.5f, 0.5f, 0.0f,1.0f,0.0f,
         0.5f, 0.5f, 0.5f, 0.0f,1.0f,0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f,1.0f,0.0f,
        -0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f
    };

    float verticiTriangolo[] = {


        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,

        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,

        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f

    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Shader
    auto compileShader = [](GLenum type, const char* src) {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        return shader;
        };
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glEnable(GL_DEPTH_TEST);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    // Variabili FPS
    double previousTime = glfwGetTime();
    int frameCount = 0;

    // Loop principale
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        frameCount++;

        // Aggiorna FPS ogni secondo
        if (currentTime - previousTime >= 1.0) {
            std::ostringstream title;
            title << "graphicEngine - FPS: " << frameCount
                << " | Size: " << fbWidth << "x" << fbHeight;
            glfwSetWindowTitle(window, title.str().c_str());
            frameCount = 0;
            previousTime = currentTime;
        }

        glfwPollEvents();
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
            (float)glfwGetTime() * glm::radians(45.0f),
            glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            (float)fbWidth / fbHeight,
            0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glUniform3f(glGetUniformLocation(shaderProgram, "lightDir"), -0.5f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.3f, 0.8f, 0.5f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}