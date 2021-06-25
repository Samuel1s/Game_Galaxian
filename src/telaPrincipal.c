#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/variaveisGlobais.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/colisao.h"
#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaInimigo.h"
#include "./library/criaMisseis.h"

void desenhaMinhaCena() {
    // cor para limpar a tela
    glClearColor(1, 1, 1, 1);      
    glClear(GL_COLOR_BUFFER_BIT);
    
    desenhaNaveInimiga();
    desenhaNaveHeroi(posicao_heroi_x, posicao_heroi_y);
  

    desenhaMisseis(misseis_nave_heroi);
    desenhaMisseis(misseis_nave_inimigas);

    detectaColisaoNaveHeroi();
    detectaColisaoNaveInimiga();

    glutSwapBuffers();
    glFlush();
}