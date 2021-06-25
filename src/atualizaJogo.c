#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "./library/teclado.h"
#include "./library/colisao.h"
#include "./library/criaMissil.h"
#include "./library/criaMisseis.h"
#include "./library/criaObjetos.h"
#include "./library/variaveisGlobais.h"

int timer = 0;

void controleInimigos()
{
  //SORTEAR INIMIGO ALEATORIO PARA ATIRAR
  timer++;
  if(timer == 33)
  {
      srand(time(0));
      int i = rand() % M_I;
      int j = rand() % M_J;
      timer = 0;

      if(naves_inimigas[i][j].status_flag == 1)
      {
        defineMisseisInimigos(misseis_nave_inimigas, -1, naves_inimigas[i][j]);
      }
      else
      {
        controleInimigos();
      }
  }
}

void controleHeroi()
{
  //SE APERTAR O ESPAÇO
  if(flag_controle_missil == 1)
  {
    defineMisseisHeroi(misseis_nave_heroi ,1);
    desenhaMisseis(misseis_nave_heroi);
    flag_controle_missil = 0;
  }
}

void atualizaCena()
{  
  controleHeroi();
  controleInimigos();
  glutPostRedisplay();
      
  glutTimerFunc(33, atualizaCena, 0);
}
