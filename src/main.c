#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "./library/teclado.h"
#include "./library/colisao.h"
#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaInimigo.h"
#include "./library/criaObjetos.h"
#include "./library/criaMisseis.h"
#include "./library/atualizaJogo.h"
#include "./library/telaPrincipal.h"
#include "./library/variaveisGlobais.h"

#include "teclado.c"
#include "colisao.c"
#include "defineHeroi.c"
#include "atualizaJogo.c"
#include "defineMisseis.c"
#include "defineInimigo.c"
#include "defineObjetos.c"
#include "telaPrincipal.c"

void redimensionada(int width, int height)
{
   // left, bottom, right, top
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(gl_world_begin_x, gl_world_end_x, gl_world_begin_y, gl_world_end_y, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
}

void setup() {
    criandoInimigos(); 
    
    criandoVetorDeMisseis(misseis_nave_heroi);
    criandoVetorDeMisseis(misseis_nave_inimigas);
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
    setup();

    // abre a janela
    glutCreateWindow("Galaxian - Teste");

    // registra callbacks para alguns eventos
    glutDisplayFunc(desenhaMinhaCena);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(teclaPressionada);
    //glutKeyboardUpFunc(teclaPressionadaUp);
    glutSpecialFunc(teclaEspecialPressionada);
    glutTimerFunc(33, atualizaCena, 0);
    
    // entra em loop e nunca sai
    glutMainLoop();
    return 0;
}