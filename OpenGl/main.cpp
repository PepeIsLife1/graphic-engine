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
#include "shaderClass.h"

#define MAXVERICES 1024
#define MAXERROR 100

// Variabili globali
GLFWwindow* window;
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
char error[MAXERROR];
FILE* errorFile;
FILE* verticesBufferFile;
float verticesBuffer[MAXVERICES];
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};
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

    Shader shaderProgram("default.vert", "default.frag");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    int risultato = 0;

    //Mentre la finestra e' aperta lui trova la larghezza e l'altezza della finestra
    //e calcola i frame per secondo bloccandosi al refresh rate del monitor
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        frameCount++;
        shaderProgram.Activate();

        risultato = frameCount / 60;

        // Aggiorna FPS ogni secondo
        if (currentTime - previousTime >= 1.0) {
            frameCount = frameCount / risultato;
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
        glClearColor(0.2f, 0.2f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);

    }
    glfwDestroyWindow(window);
    shaderProgram.Delete();
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

