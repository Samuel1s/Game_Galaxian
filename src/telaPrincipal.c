#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/colisao.h"
#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaInimigo.h"
#include "./library/criaMisseis.h"
#include "./library/telaPrincipal.h"
#include "./library/variaveisGlobais.h"

void desenhaFundo(GLuint tx, int x_begin, int y_begin, int x_end, int y_end)
{
  glColor3f(1.0, 1.0, 1.0);//BRANCO
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tx);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0); glVertex2f(x_begin, y_begin);    // v3---v2
      glTexCoord2f(1, 0); glVertex2f(x_end, y_begin);      // |     |
      glTexCoord2f(1, 1); glVertex2f(x_end, y_end);        // |     |
      glTexCoord2f(0, 1); glVertex2f(x_begin,  y_end);     // v0---v1
    glEnd();
  glDisable(GL_TEXTURE_2D);
}

void escreveTexto(void * font, char *s, float x, float y, float z) // FUNCAO PARA ESCREVER TEXTO
{ 
  int i;
  glRasterPos3f(x, y, z);
  glPushMatrix();
    for (i = 0; i < strlen(s); i++) 
    {
      glutBitmapCharacter(font, s[i]);
    }
  glPopMatrix();
}

void desenhaTelaTutorial()
{
  glClear(GL_COLOR_BUFFER_BIT);
    desenhaFundo(tx_Fundo_Tutorial, 0, 0, 100, 100);
    glColor3f(1.0,0.0,0.0);// Vermelho
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"TUTORIAL", 36.2 , 93, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"PARA MOVIMENTACAO", 30, 80, 0);
    desenhaFundo(tx_Desenho_Mouse, 10, 65, 30, 75);
    desenhaFundo(tx_Desenho_Arrows, 40, 65, 60, 75);
    desenhaFundo(tx_Desenho_A_D, 70, 65, 90, 75);
    glColor3f(1.0,0.0,0.0);// Vermelho
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"PARA ATIRAR", 37.5, 50, 0);
    desenhaFundo(tx_Desenho_Space, 40, 40, 60, 49);
    glColor3f(1.0,0.0,0.0);// Vermelho
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"PRESSIONE ENTER PARA COMERCAR", 5, 26, 0);
    desenhaFundo(tx_Desenho_Enter, 40, 15, 60, 24);
    glColor3f(1.0,0.0,0.0);// Vermelho
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"DESENVOLVIDO POR: Samuel Santos", 20, 3, 0);
  glFlush();
}

void desenhaMinhaCena() 
{
  // cor para limpar a tela
  glClearColor(1, 1, 1, 1);      
  glClear(GL_COLOR_BUFFER_BIT);

  if (flag_status_start == 1) {
    flag_status_pause = 1;
    desenhaTelaTutorial();
    criandoInimigos(); 
    criandoVetorDeMisseis(misseis_nave_heroi);
    criandoVetorDeMisseis(misseis_nave_inimigas);
  }
  else
  {

    desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);
    desenhaNaveInimiga();
    desenhaNaveHeroi(posicao_heroi_x, posicao_heroi_y);
    desenhaMisseis(misseis_nave_heroi);
    desenhaMisseis(misseis_nave_inimigas);
    detectaColisaoNaveHeroi();
    detectaColisaoNaveInimiga();
  }

  glFlush();
}

void desenhaTelaPause()
{
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);

  if(flag_status_pause == 1 )
  {
    glColor3f(1.0,0.0,0.0);//VERMELHO
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"PAUSE", 42 + aspecto_tela_horizontal/gl_world_end_x ,90 + aspecto_tela_vertical/gl_world_end_y, 0);//PAUSE TOPO
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"CONTINUE ->P", 37 + aspecto_tela_horizontal/gl_world_end_x ,60 + aspecto_tela_vertical/gl_world_end_y, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"REINICIAR ->R", 37 + aspecto_tela_horizontal/gl_world_end_x ,40 + aspecto_tela_vertical/gl_world_end_y, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"SAIR ->ESC", 39.5 + aspecto_tela_horizontal/gl_world_end_x ,20 + aspecto_tela_vertical/gl_world_end_y, 0);
  }
  else
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);//BRANCO
    desenhaMinhaCena();
  }
  glFlush();
}

void desenhaTelaConfirmacao()
{
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);

  glColor3f(1.0,0.0,0.0);//VERMELHO
  if ((flag_status_reset == -1) && (flag_status_exit != 1))
  {
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "DESEJA REALMENTE RESETAR? Y/N", 21, 50, 0);
  }
  if (flag_status_exit == 1)
  {
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "DESEJA REALMENTE SAIR? Y/N", 21, 50, 0);
  }
  glFlush();
}

void desenhaTelaGameOver()
{
  flag_status_pause = 1;
  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);


  glColor3f(1.0,0.0,0.0);//AMARELO
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER!!!", 28, 80, 0);

  glColor3f(1.0,0.0,0.0);//VERMELHO
  escreveTexto(GLUT_BITMAP_HELVETICA_18,"PRESSIONE R PARA REINICIAR", 22.6, 20, 0);
  

  posicao_heroi_x = -50.0;
  if(flag_status_pause == 1)
  {
    flag_status_pause *= -1; 
      for(int i=0; i< M_I;i++)
      {
        for(int j=0; j<M_J;j++)
        {
          naves_inimigas[i][j].posicao.y =-80; // PARA NÃO DESENHAR OS INIMOS NA JANELA
        }
      }
    }
}
