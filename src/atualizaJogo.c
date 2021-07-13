#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/teclado.h"
#include "./library/colisao.h"
#include "./library/criaMissil.h"
#include "./library/criaMisseis.h"
#include "./library/criaObjetos.h"
#include "./library/atualizaJogo.h"
#include "./library/variaveisGlobais.h"

void movimentoNaveInimigaEixoX(int value) {
  for(int i = 0; i < M_I ; i++)
    {
    for( int j = 0; j < M_J; j++)
    {
      naves_inimigas[i][j].posicao.x += value * 0.8;
    }
  }
}

void movimentoNaveInimigaEixoY() {
  for(int i = 0; i < M_I ; i++)
  {
    // Numero aleatorio entre um intervalo: rand() % (max_number + 1 - minimum_number) + minimum_number
    posicao_aleatoria = rand() % (3 + 1 - 1) + 1;
    for( int j = 0; j < M_J ; j++)
    {
      naves_inimigas[i][j].posicao.y-= posicao_aleatoria * 1.3; 
      naves_inimigas[i][j].posicao.x-= posicao_aleatoria + 1;   
    }
  }
  posicao_aleatoria = 0;
}

void contoleMisseisInimigos()
{
  //SORTEAR INIMIGO ALEATORIO PARA ATIRAR
  respawn_missil_inimigo ++;
  if(respawn_missil_inimigo == 20)
  {
      srand(time(0));
      int i = rand() % M_I;
      int j = rand() % M_J;
      respawn_missil_inimigo = 0;

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

// FIXME: Que tal definir um timer com movimento
void movimentaNaveInimiga()
{
  switch (flag_muda_direcao_nave_inimiga)
  {
    case 1:
      if((naves_inimigas[0][8].posicao.x + naves_inimigas[0][8].dimensao.x/2) < gl_world_end_x)
      {
        movimentoNaveInimigaEixoX(1);
      }
      else
      {
        movimentoNaveInimigaEixoY();
        flag_muda_direcao_nave_inimiga *= -1;
      }
      break;

    case -1:
      if(naves_inimigas[0][0].posicao.x > (gl_world_begin_x + naves_inimigas[0][0].dimensao.x/2))
      {
        movimentoNaveInimigaEixoX(-1);
      }
      else
      {
        movimentoNaveInimigaEixoY();
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
  /* A cada 2000 de pontos ganha uma vida extra */
  if (placar > 2000) {
    flag_vidas_restantes ++;
    placar = 0;
  }
  
  if (flag_status_pause != 1) 
  {
    controleMisseisHeroi();
    contoleMisseisInimigos();
    movimentaNaveInimiga();
    glutPostRedisplay();
  }
    glutTimerFunc(33, atualizaCena, 0);
}
