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
int aux = 0.6;


void contoleMisseisInimigos()
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
        contoleMisseisInimigos();
      }
  }
}


void movimentaNaveInimiga()
{

  // rand() % (max_number + 1 - minimum_number) + minimum_number
  //INIMIGO ANDANDO PARA A DIREITA
  switch (flag_muda_direcao_nave_inimiga)
  {
  case 1:
    if((naves_inimigas[0][8].posicao.x + naves_inimigas[0][8].dimensao.x/2) < gl_world_end_x)
    {
      for(int i = 0; i < M_I ; i++)
      {
        for( int j = 0; j < M_J ; j++)
        {
            naves_inimigas[i][j].posicao.x += 1;
        }
      }
    }
    else
    {
      for(int i = 0; i < M_I ; i++)
      {
        for( int j = 0; j < M_J ; j++)
        {
            naves_inimigas[i][j].posicao.y-= 1;
        }
      }
      flag_muda_direcao_nave_inimiga *= -1;
    }
    break;
  case -1:

    if(naves_inimigas[0][0].posicao.x > (gl_world_begin_x + naves_inimigas[0][0].dimensao.x/2))
    {
      for(int i = 0; i < M_I ; i++)
      {
        for( int j = 0; j < M_J ; j++)
        {
            naves_inimigas[i][j].posicao.x-= 1;
            multiplicador_de_placar += 0.01;
        }
      }
    }
    else
    {
      for(int i = 0; i < M_I ; i++)
      {
        for( int j = 0; j < M_J ; j++)
        {
            naves_inimigas[i][j].posicao.y-= 1;
        }
      }
      flag_muda_direcao_nave_inimiga *= -1;
    }
    break;

  default:
    break;
  }
}

void controleMisseisHeroi()
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
  controleMisseisHeroi();
  contoleMisseisInimigos();
  movimentaNaveInimiga();
  glutPostRedisplay();
      
  glutTimerFunc(33, atualizaCena, 0);
}
