#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "./library/teclado.h"
#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaObjetos.h"
#include "./library/criaMisseis.h"
#include "./library/variaveisGlobais.h"


double calculoColisaoFronteira(Avatar nave_inimiga, Missil missil)
{
  double somaDosQuadradosDiferenca = pow((nave_inimiga.posicao.x - missil.posicao_missil_x), 2) + pow((nave_inimiga.posicao.y - missil.posicao_missil_y), 2);
  double raizSoma = sqrt(somaDosQuadradosDiferenca);
  return raizSoma;
}


// MISSIL DO INIMIGO COM O PLAYER
void detectaColisaoNaveHeroi()
{
  if(flag_vidas_restantes == 0)
  {
    teclaPressionada(27, 1 , 1); // Finalizao do jogo.
  }

  for(int i = 0; i < quantiddade_misseis_inimigos; i++)
  {
    if(calculoColisaoFronteira(nave_heroi, misseis_nave_inimigas[i])  < nave_heroi.dimensao.y/2)
    {
      flag_vidas_restantes--;
      misseis_nave_inimigas[i].posicao_missil_y = -50;
    }
  }
}


// MISSIL DO PLAYER COM INIMIGOS
void detectaColisaoNaveInimiga()
{
  for(int i = 0; i < M_I; i++)
  {
    for(int j = 0; j < M_J; j++)
    {
      for(int t = 0; t < quantidade_misseis_heroi; t++)
      {
        if(calculoColisaoFronteira(naves_inimigas[i][j], misseis_nave_heroi[t]) < naves_inimigas[i][j].dimensao.x/2 && naves_inimigas[i][j].status_flag == 1)
        {
          misseis_nave_heroi[t].posicao_missil_x = -5;
          naves_inimigas[i][j].status_flag = 0;
          naves_inimigas[i][j].posicao.y = -100;
          flag_inimigos_mortos++;
          placar += naves_inimigas[i][j].posicao.y*multiplicador_de_placar;
        }

      }
    }
  }
}

