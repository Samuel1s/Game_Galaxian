#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaObjetos.h"
#include "./library/criaMisseis.h"
#include "./library/variaveisGlobais.h"

void desenhaMisseis(Missil * missil)
{
  for(int i = 0; i < quantidade_misseis_criados; i++)
  {

    m_v0.x = missil[i].posicao_missil_x - missil[i].dimensao_missil_x / 2;
    m_v0.y = missil[i].posicao_missil_y - missil[i].dimensao_missil_y / 2;

    m_v1.x = missil[i].posicao_missil_x + missil[i].dimensao_missil_x / 2;
    m_v1.y = missil[i].posicao_missil_y - missil[i].dimensao_missil_y / 2;

    m_v2.x = missil[i].posicao_missil_x + missil[i].dimensao_missil_x / 2;
    m_v2.y = missil[i].posicao_missil_y + missil[i].dimensao_missil_y / 2;

    m_v3.x = missil[i].posicao_missil_x - missil[i].dimensao_missil_x / 2;
    m_v3.y = missil[i].posicao_missil_y + missil[i].dimensao_missil_y / 2;
   

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0);
      glVertex2f(m_v0.x, m_v0.y);

      glTexCoord2f(1, 0);
      glVertex2f(m_v1.x, m_v1.y);

      glTexCoord2f(1, 1);
      glVertex2f(m_v2.x, m_v2.y);

      glTexCoord2f(0, 1);
      glVertex2f(m_v3.x, m_v3.y);
    glEnd();
    glutPostRedisplay();

    if(missil[i].orientacao == -1)
    {
      missil[i].posicao_missil_y -= missil[i].velocidade_missil;

    } 
    else if (missil[i].orientacao == 1) 
    {
      missil[i].posicao_missil_y += missil[i].velocidade_missil;
    }
  }
}

void criandoVetorDeMisseis(Missil * misseis)
{
    for(int i = 0; i < quantidade_misseis_criados; i++)
    {
      misseis[i].orientacao = 0;
      misseis[i].posicao_missil_x = -5;
      misseis[i].posicao_missil_y = 0;  
      misseis[i].dimensao_missil_x = 0.7;
      misseis[i].dimensao_missil_y = 0.7;
      misseis[i].velocidade_missil = 0.1;
    }
}

void defineMisseisHeroi(Missil * misseis, int sentido_missil)
{
  for(int i = 0; i < quantidade_misseis_criados; i++)
  {

    if(misseis[i].posicao_missil_x == -5.0)
    {
      misseis[i].posicao_missil_x = posicao_heroi_x;
      misseis[i].posicao_missil_y = posicao_inicial_missil;
      misseis[i].orientacao = sentido_missil;
      i = quantidade_misseis_criados;

    }
    else if(i == quantidade_misseis_criados - 1)
    {
      misseis[limite_misseis].posicao_missil_x = posicao_heroi_x;
      misseis[limite_misseis].posicao_missil_y = posicao_inicial_missil;
      misseis[limite_misseis].orientacao = sentido_missil;
      limite_misseis++;

      if(limite_misseis == quantidade_misseis_criados)
        limite_misseis = 0;
    }
  }
}

void defineMisseisInimigos(Missil * misseis, int sentido_missil, Avatar heroi)
{
  for(int i = 0; i < quantidade_misseis_criados; i++)
  {
    if(misseis[i].posicao_missil_x == -5)
    {
      misseis[i].posicao_missil_x = heroi.posicao.x;
      misseis[i].posicao_missil_y = heroi.posicao.y;
      misseis[i].orientacao = sentido_missil;
      i = quantidade_misseis_criados;

    }
    else if(i == quantidade_misseis_criados - 1)
    {
      misseis[limite_misseis].posicao_missil_x = heroi.posicao.x;
      misseis[limite_misseis].posicao_missil_y = heroi.posicao.y;
      misseis[limite_misseis].orientacao = sentido_missil;
      limite_misseis++;

      if(limite_misseis == quantidade_misseis_criados)
        limite_misseis = 0;
    }
  }
}