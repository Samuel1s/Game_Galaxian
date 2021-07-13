#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <GL/freeglut.h>
#include <SDL/SDL_mixer.h>

#include "./library/colisao.h"
#include "./library/criaHeroi.h"
#include "./library/criaMissil.h"
#include "./library/criaInimigo.h"
#include "./library/criaMisseis.h"
#include "./library/telasDoJogo.h"
#include "./library/carregaMusica.h"
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

/******************************************************************************
                          DESENHA TELA TUTORIAL
*******************************************************************************/

void desenhaTelaTutorial()
{
  /*Overwrite*/
  calculo_aspecto_horizontal = aspecto_tela_horizontal/gl_world_end_x + controle_razao_janela;
  calculo_aspecto_vertical = aspecto_tela_vertical/gl_world_end_y + controle_razao_janela;


  flag_status_vencedor *= -1;

  glClear(GL_COLOR_BUFFER_BIT);
    desenhaFundo(tx_Fundo_Tutorial, 0, 0, 100, 100);
    glColor3f(0.0,1.0,0.0);// VERDE
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"TUTORIAL", 36.2 + calculo_aspecto_horizontal , 93.0 + calculo_aspecto_vertical, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"PARA MOVIMENTACAO", 30.0 + calculo_aspecto_horizontal, 80.0 + calculo_aspecto_vertical, 0);
    desenhaFundo(tx_Desenho_Arrows, 10, 65, 30, 75);
    desenhaFundo(tx_Desenho_Mouse, 40, 65, 60, 75);
    desenhaFundo(tx_Desenho_A_D, 70, 65, 90, 75);
    glColor3f(0.0,1.0,0.0);// VERDE
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"PARA ATIRAR", 37.5 + calculo_aspecto_horizontal, 50.0 + calculo_aspecto_vertical, 0);
    desenhaFundo(tx_Desenho_Space, 40, 40, 60, 49);
    glColor3f(0.0,1.0,0.0);// VERDE
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"PRESSIONE ENTER PARA COMERCAR", 5.0 + calculo_aspecto_horizontal, 26.0 + calculo_aspecto_vertical, 0);
    desenhaFundo(tx_Desenho_Enter, 40, 15, 60, 24);
    glColor3f(0.0,1.0,0.0);// VERDE
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"VOCE COMECA COM 2 VIDAS", 20.0 + calculo_aspecto_horizontal, 3.0 + calculo_aspecto_vertical, 0);
    desenhaFundo(tx_Desenho_Vida, 10, 1, 20, 11);
  glFlush();
}

/******************************************************************************
                          DESENHA TELA JOGO
*******************************************************************************/

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
    
    Mix_PlayMusic(musica_jogo,0);
    Mix_PlayMusic(musica_jogo,-1);
  }
  else
  {
    desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);
    if (flag_status_vencedor == 1) {
      desenhaNaveHeroi(posicao_heroi_x, posicao_heroi_y);
    }
    desenhaMisseis(misseis_nave_heroi);
    desenhaMisseis(misseis_nave_inimigas);
    desenhaNaveInimiga();
    detectaColisaoNaveHeroi();
    detectaColisaoNaveInimiga();
    hudDisplay();
  }

  glFlush();
}

/******************************************************************************
                          DESENHA TELA PAUSE
*******************************************************************************/

void desenhaTelaPause()
{

  /*Overwrite*/
  calculo_aspecto_horizontal = aspecto_tela_horizontal/gl_world_end_x + controle_razao_janela;
  calculo_aspecto_vertical = aspecto_tela_vertical/gl_world_end_y + controle_razao_janela;

  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);

  if(flag_status_pause == 1 && flag_status_exit != 1)
  {
    glColor3f(0.0,1.0,0.0);// VERDE
    escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"PAUSE", 42.0 + calculo_aspecto_horizontal, 90 +  calculo_aspecto_vertical, 0);//PAUSE TOPO
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"CONTINUE ->P", 37.0 + calculo_aspecto_horizontal, 60 + calculo_aspecto_vertical, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"REINICIAR ->R", 37 + calculo_aspecto_horizontal, 40 + calculo_aspecto_vertical, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"SAIR ->ESC", 39.5 + calculo_aspecto_horizontal, 20 + calculo_aspecto_vertical, 0);
  }
  else
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);//BRANCO
    desenhaMinhaCena();
  }
  glFlush();
}

/******************************************************************************
                          DESENHA TELA CONFIRMACAO
*******************************************************************************/

void desenhaTelaConfirmacao()
{
  /*Overwrite*/
  calculo_aspecto_horizontal = aspecto_tela_horizontal/gl_world_end_x + controle_razao_janela;
  calculo_aspecto_vertical = aspecto_tela_vertical/gl_world_end_y + controle_razao_janela;

  glClear(GL_COLOR_BUFFER_BIT);
  
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);

  glColor3f(0.0,1.0,0.0);// VERDE
  if ((flag_status_reset == -1) && (flag_status_exit != 1))
  {
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "DESEJA REALMENTE RESETAR? Y/N", 21 + calculo_aspecto_horizontal, 50 + calculo_aspecto_vertical, 0);
  }
  if (flag_status_exit == 1)
  {
    escreveTexto(GLUT_BITMAP_HELVETICA_18, "DESEJA REALMENTE SAIR? Y/N", 21 + calculo_aspecto_horizontal, 50 + calculo_aspecto_vertical, 0);
  }
  glFlush();
}

/******************************************************************************
                          DESENHA TELA GAME OVER
*******************************************************************************/

void desenhaTelaGameOver()
{
  /*Overwrite*/
  calculo_aspecto_horizontal = aspecto_tela_horizontal/gl_world_end_x + controle_razao_janela;
  calculo_aspecto_vertical = aspecto_tela_vertical/gl_world_end_y + controle_razao_janela;

  flag_status_pause = 1;
  flag_status_vencedor = -1;

  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);


  glColor3f(0.0,1.0,0.0);//AMARELO
  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER!!!", 28 + calculo_aspecto_horizontal, 80 + calculo_aspecto_vertical, 0);

  glColor3f(0.0,1.0,0.0);// VERDE
  escreveTexto(GLUT_BITMAP_HELVETICA_18,"PRESSIONE ESC PARA SAIR", 22.6 + calculo_aspecto_horizontal, 20 + calculo_aspecto_vertical, 0);
  
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

  glFlush();
}

/******************************************************************************
                          DESENHA TELA VENCEDOR
*******************************************************************************/

void desenhaTelaVencedor()
{

  /*Overwrite*/
  calculo_aspecto_horizontal = aspecto_tela_horizontal/gl_world_end_x + controle_razao_janela;
  calculo_aspecto_vertical = aspecto_tela_vertical/gl_world_end_y + controle_razao_janela;
  flag_status_pause = 1;
  flag_status_vencedor *= -1;
  
  posicao_heroi_x = -50.0;

  glClear(GL_COLOR_BUFFER_BIT);
  desenhaFundo(tx_Fundo_Jogo, 0, 0, 100, 100);
  glColor3f(1.0,1.0,1.0);// BRANCO

  escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24,"VOCE VENCEU", 33.3 + calculo_aspecto_horizontal, 65 + calculo_aspecto_vertical, 0);

  glColor3f(0.0,1.0,0.0);// VERDE
  escreveTexto(GLUT_BITMAP_HELVETICA_18,"PRESSIONE ESC PARA SAIR", 22.6 + calculo_aspecto_horizontal, 20 + calculo_aspecto_vertical, 0);

  escreveTexto(GLUT_BITMAP_HELVETICA_18,"PRODUZIDO BY: SAMUEL FILIPE DOS SANTOS", 6.5 + calculo_aspecto_horizontal, 10 + calculo_aspecto_vertical, 0);
  
  if(flag_verifica_musica == 1)
  {
    Mix_PlayMusic(musica_vencedor, 0);
    Mix_PlayMusic(musica_vencedor, -1);
    musica_vencedor = 0;
  }
 
 glFlush();
     
}

/******************************************************************************
                          DESENHA CORACOES
*******************************************************************************/

void desenhaVidasRestantes(float p_x, float p_y)
{
  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < flag_vidas_restantes; j++)
    {
      display_vida[i][j] = criaObjetos(p_x, p_y, dim_x_vida, dim_y_vida);
      p_x = p_x + 10;

      glColor4f(1.0, 1.0, 1.0, 1.0);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, tx_Desenho_Vida);

      v_v0.x = -display_vida[i][j].dimensao.x/2;
      v_v0.y = -display_vida[i][j].dimensao.y/2;

      v_v1.x = display_vida[i][j].dimensao.x/2;
      v_v1.y = -display_vida[i][j].dimensao.y/2;

      v_v2.x = display_vida[i][j].dimensao.x/2;
      v_v2.y = display_vida[i][j].dimensao.y/2;

      v_v3.x = -display_vida[i][j].dimensao.x/2;
      v_v3.y =  display_vida[i][j].dimensao.y/2;

      glPushMatrix();                 
        glTranslatef(display_vida[i][j].posicao.x, display_vida[i][j].posicao.y, 0);
          glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(v_v0.x, v_v0.y, 0);
            glTexCoord2f(1, 0); glVertex3f(v_v1.x, v_v1.y, 0);
            glTexCoord2f(1, 1); glVertex3f(v_v2.x, v_v2.y, 0);
            glTexCoord2f(0, 1); glVertex3f(v_v3.x, v_v3.y, 0);
          glEnd();
      glPopMatrix();                
      
      glDisable(GL_TEXTURE_2D);
    }
  }
  glFlush();
}

/******************************************************************************
                          DESENHA COIN
*******************************************************************************/

void desenhaCoin(float p_x, float p_y)
{
  
  display_coin_vida = criaObjetos(p_x, p_y, dim_x_coin_vida, dim_y_coin_vida);

  glColor4f(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tx_Desenho_Coin);

  c_v0.x = -display_coin_vida.dimensao.x/2;
  c_v0.y = -display_coin_vida.dimensao.y/2;

  c_v1.x = display_coin_vida.dimensao.x/2;
  c_v1.y = -display_coin_vida.dimensao.y/2;

  c_v2.x = display_coin_vida.dimensao.x/2;
  c_v2.y = display_coin_vida.dimensao.y/2;

  c_v3.x = -display_coin_vida.dimensao.x/2;
  c_v3.y =  display_coin_vida.dimensao.y/2;

  glPushMatrix();                 
    glTranslatef(display_coin_vida.posicao.x, display_coin_vida.posicao.y, 0);
      glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(c_v0.x, c_v0.y, 0);
        glTexCoord2f(1, 0); glVertex3f(c_v1.x, c_v1.y, 0);
        glTexCoord2f(1, 1); glVertex3f(c_v2.x, c_v2.y, 0);
        glTexCoord2f(0, 1); glVertex3f(c_v3.x, c_v3.y, 0);
      glEnd();
    glPopMatrix();                  
  glDisable(GL_TEXTURE_2D);
    
  glFlush();
}

/******************************************************************************
                          DISPLAY HUD
*******************************************************************************/

void hudDisplay()
{
  if (flag_status_vencedor == 1) {
    glColor3f(1.0,1.0,1.0);//BRANCO
    sprintf(placar_show_display, "2000/ %.0f", placar);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,"", 75, 5, 0);
    escreveTexto(GLUT_BITMAP_HELVETICA_18,placar_show_display, 80, 5, 0);
    desenhaVidasRestantes(p_x_vida_inicial, p_y_vida_inicial);      
    desenhaCoin(75, 5);
  }
  glFlush();

}