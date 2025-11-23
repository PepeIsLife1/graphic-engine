#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>
#include <direct.h>

#define MAXVERICES 1024
#define MAXERROR 100


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





// Variabili globali
GLFWwindow* window;
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
char error[MAXERROR];
FILE* errorFile;
FILE* verticesBufferFile;
float verticesBuffer[MAXVERICES];
// Variabili globali





// Dichiarazione funzioni
int modelLoader();

void worldGeneration();

void entityHandle();

void inputHandle();

int windowHandle();

int handleGUI();

void gameLoop();

void dayCicle();

void timePassed();

int errorLogger(char error[MAXERROR]);

void verticesBufferFileWriter();
//Dichiarazione funzioni





//Inizio codice
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Callback ridimensionamento oggetti
    glViewport(0, 0, width, height);
}


int main() {

    gameLoop();
}

void gameLoop() {

    windowHandle();
    modelLoader();
}

int windowHandle() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "graphicEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Errore creazione finestra\n";
        char errore[MAXERROR] = "Errore creazione finestra";
        errorLogger(errore);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Errore inizializzazione GLAD\n";
        return -1;
    }

    int fbWidth, fbHeight;
    int frameCount = 0;
    double previousTime = glfwGetTime();

    //Mentre la finestra e' aperta lui trova la larghezza e l'altezza della finestra
    //e calcola i frame per secondo bloccandosi al refresh rate del monitor
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
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
        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(0.2f, 0.2f, 0.5f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    return 0;
}

int errorLogger(char error[MAXERROR]) {
    errorFile = NULL;
    errno_t err = fopen_s(&errorFile, "errorLogger.txt", "a");
    if (errorFile == 0)
        return 0;
    for (int i = 0;i < MAXERROR;i++) {
        fwrite(&error[i], sizeof(char), 1, errorFile);
    }
    fprintf(errorFile, "\n");
    fclose(errorFile);
}

int modelLoader() {
    verticesBufferFile = NULL;
    errno_t err = fopen_s(&verticesBufferFile, "verticesBufferFile.txt", "a");
    if (verticesBufferFile == 0) {
        char error[MAXERROR] = "file vertici non trovato";
        errorLogger(error);
        return 0;
    }

    

}

