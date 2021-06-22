#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>


#include "criaObjetos.h"
#include "criaObjetos.c"
#include "criaHeroi.h"
#include "criaHeroi.c"
#include "criaInimigo.h"
#include "criaInimigo.c"


void desenhaMinhaCena() {
    // cor para limpar a tela
    glClearColor(1, 1, 1, 1);      
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0); 
    criandoInimigos();   
    desenhaNaveInimiga();
    desenhaHeroi(50.0, 0.0);

    glFlush();
}

void redimensionada(int width, int height)
{
   // left, bottom, right, top
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 100, 0, 100, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
}

void teclaPressionada(unsigned char key, int x, int y)
{
    // ve qual tecla foi pressionada
    switch(key)
    {
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicacao
        break;
    }
}

int main(int argc, char **argv)
{
    // acordando o GLUT
    glutInit(&argc, argv);

    // definindo a versao do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // configuracao inicial da janela do GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // abre a janela
    glutCreateWindow("Galaxian - Teste");

    // registra callbacks para alguns eventos
    glutDisplayFunc(desenhaMinhaCena);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(teclaPressionada);
    
   
    // entra em loop e nunca sai
    glutMainLoop();
    return 0;
}