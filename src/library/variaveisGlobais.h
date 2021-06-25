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
                          VARIAVEIS DO HEROI
*******************************************************************************/
// Dimensao NAVE HEROI
#define dim_x_nave_heroi 10
#define dim_y_nave_heroi 10

// Definicao
Avatar nave_heroi;

// Textura
GLuint id_Avatar_Heroi;

// Vertices de posicionamento da nave heroi.
Vetor_2d h_v0, h_v1, h_v2, h_v3; 

// Outros
float posicao_heroi_x = 50.0;
float posicao_heroi_y = 0.0;

// Controle
int flag_vidas_restantes = 3;
int placar = 0;
float multiplicador_de_placar = 0.01;

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
GLuint id_Avatar_Inimigo;

// Controle
int flag_inimigos_mortos;

/******************************************************************************
                          VARIAVEIS DOS MISSEIS
*******************************************************************************/
#define posicao_inicial_missil 10
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


#endif