#ifndef _VARIAVEIS_GLOBAIS_H_
#define _VARIAVEIS_GLOBAIS_H_

#include "criaMissil.h"
#include "criaObjetos.h"

/*
    Foi parametrizado um mundo 100 x 100.

      _______ World_Begin_y________     
     |              |              |
     |              |              |
World|              |              |World
Begin|______________|(0,0)_________|end                           
    x|              |              |x
     |              |              |
     |              |              |
     |______________|______________|
               World_End_y
*/

/******************************************************************************
                          VARIAVEIS DO MUNDO
*******************************************************************************/
int gl_world_begin_x = 0;
int gl_world_end_x = 100;
int gl_world_begin_y = 0;
int gl_world_end_y = 100;

/******************************************************************************
                          VARIAVEIS DO JOGO
*******************************************************************************/
float controle_razao_janela;
float aspecto_tela_vertical;
float aspecto_tela_horizontal;

float calculo_aspecto_horizontal;
float calculo_aspecto_vertical;

Vetor_2d posicao_mouse;

Mix_Music *musica_jogo = NULL;
Mix_Music *musica_vencedor = NULL;

int flag_verifica_musica = 1;
/******************************************************************************
                          VARIAVEIS DO HEROI
*******************************************************************************/
// Dimensao NAVE HEROI.
#define dim_x_nave_heroi 10
#define dim_y_nave_heroi 10

// Dimensao VIDA HEROI 'Corações'.
#define dim_x_vida 8
#define dim_y_vida 8

// Dimensa COIN GANHA VIDA.
#define dim_x_coin_vida 15
#define dim_y_coin_vida 10

// Definicao
Avatar nave_heroi;

// Show data vida - Display - o 10 é para ter espaço para redesenhar.
Avatar display_vida[1][10];

// Coin - Display 
Avatar display_coin_vida;

// Textura
GLuint tx_Nave_Heroi;

// Textura Vida Heroi
GLuint tx_Desenho_Vida;

// Textura coin vida
GLuint tx_Desenho_Coin;

// Vertices de posicionamento da nave heroi.
Vetor_2d h_v0, h_v1, h_v2, h_v3; 

// Vértices da vida do heroi.
Vetor_2d v_v0, v_v1, v_v2, v_v3; 

// Vértices da coin ganha vida.
Vetor_2d c_v0, c_v1, c_v2, c_v3; 

// Outros
float posicao_heroi_x = 50.0;
float posicao_heroi_y = 10.0;
float p_x_vida_inicial= 10;
float p_y_vida_inicial = 3;

char placar_show_display[100];

// Controle
float placar = 1.0;
int flag_vidas_restantes = 2;
float multiplicador_de_placar = -1.5;

/******************************************************************************
                          VARIAVEIS DO INIMIGO
*******************************************************************************/
// Dimensao e Posicao NAVE INIMIGA 
#define dim_x_nave_inimiga 5
#define dim_y_nave_inimiga 5
#define pos_x_nave_inimiga 10
#define pos_y_nave_inimiga 90

// Matriz de alocacao os inimigos
#define M_I 4
#define M_J 9

// Definicao
Avatar naves_inimigas[M_I][M_J];

// Vertices de posicionamento das naves iminigas.
Vetor_2d i_v0, i_v1, i_v2, i_v3; 

// Textura
GLuint tx_Nave_Inimiga;

// Controle
int flag_inimigos_mortos;
int flag_muda_direcao_nave_inimiga = 1;
int flag_desenha_coin = 1;
int respawn_missil_inimigo = 0;
int posicao_aleatoria = 0;

/******************************************************************************
                          VARIAVEIS DOS MISSEIS
*******************************************************************************/
#define posicao_inicial_missil 15
#define quantidade_misseis_heroi 12
#define quantidade_misseis_criados 12
#define quantiddade_misseis_inimigos 20


// Vertices de posicionamento dos misseis.
Vetor_2d m_v0, m_v1, m_v2, m_v3;

// Definicao
Missil misseis_nave_heroi[quantidade_misseis_heroi];
Missil misseis_nave_inimigas[quantiddade_misseis_inimigos];

// Controle 
int flag_controle_missil = 0;
int limite_misseis = 0;


/******************************************************************************
                          VARIAVEIS DAS TELAS
*******************************************************************************/
GLuint tx_Fundo_Jogo;
GLuint tx_Fundo_Tutorial;
GLuint tx_Tela_Inicial;
GLuint tx_Desenho_Mouse;
GLuint tx_Desenho_Space;
GLuint tx_Desenho_Enter;
GLuint tx_Desenho_Arrows;
GLuint tx_Desenho_A_D;

int flag_status_start = 1;
int flag_status_pause = -1;
int flag_status_exit = -1;
int flag_status_reset = 1;
int flag_status_yes = -1;
int flag_status_no = 1;
int flag_status_vencedor = -1;
#endif