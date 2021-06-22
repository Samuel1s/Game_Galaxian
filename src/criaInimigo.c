#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "criaObjetos.h" 
#include "criaHeroi.h"

// Dimensao NAVE INIMIGA -> comp x larg
#define dim_x_nave_inimiga 10
#define dim_y_nave_inimiga 10

// Posicao inicial e matriz de localizacao (quantidade) 
#define pos_x_nave_inimiga 10
#define pos_y_nave_inimiga 90
#define M_I 4
#define M_J 9

// Criacao da matriz
Avatar naves_inimigas[M_I][M_J];

// Textura
GLuint id_Avatar_Inimigo;

// Contador de Mortes
int flag_inimigos_mortos;

void criandoInimigos() {
    float p_y = pos_y_nave_inimiga;
    for (int i = 0; i < M_I; i++)
    {
        float p_x = pos_x_nave_inimiga;
        for (int j = 0; j  <  M_J; j++)
        {
            naves_inimigas[i][j] = criaObjetos(p_x, p_y, dim_x_nave_inimiga, dim_y_nave_inimiga);
            p_x += pos_x_nave_inimiga * 2;  
        }
        p_y -= (M_J + M_I/2); 
    }
}

void desenhaNaveInimiga() 
{
    for (int i = 0; i < M_I; i++)
    {
        for (int j = 0; j  <  M_J; j++)
        {
           if (flag_inimigos_mortos == (M_I * M_J)) 
           {
                printf("Tela de Vencedor");
           }

           if (naves_inimigas[i][j].status_flag == 1)
           {
                if (naves_inimigas[i][j].posicao.y < (fronteiraNaveHeroi()))
                {
                    printf("Tela game Over");
                }
           }
           

        glColor3f (1, 0, 0);
        // glEnable(GL_TEXTURE_2D);
        // glBindTexture(GL_TEXTURE_2D, id_Avatar_Inimigo);
        
        // Vertices de posicionamento do jeito bom.
        Vetor_2d i_v0, i_v1, i_v2, i_v3; 

        i_v0.x = -naves_inimigas[i][j].dimensao.x/2;
        i_v0.y = -naves_inimigas[i][j].dimensao.y/2;

        i_v1.x = naves_inimigas[i][j].dimensao.x/2;
        i_v1.y = -naves_inimigas[i][j].dimensao.y/2;

        i_v2.x = naves_inimigas[i][j].dimensao.x/2;
        i_v2.y = naves_inimigas[i][j].dimensao.y/2;

        i_v3.x = -naves_inimigas[i][j].dimensao.x/2;
        i_v3.y =  naves_inimigas[i][j].dimensao.y/2;


        glPushMatrix();                 
            glTranslatef(naves_inimigas[i][j].posicao.x, naves_inimigas[i][j].posicao.y, 0);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0); glVertex3f(i_v0.x, i_v0.y, 0);
                glTexCoord2f(1, 0); glVertex3f(i_v1.x, i_v1.y, 0);
                glTexCoord2f(1, 1); glVertex3f(i_v2.x, i_v2.y, 0);
                glTexCoord2f(0, 1); glVertex3f(i_v3.x, i_v3.y, 0);
            glEnd();
        glPopMatrix();                  
        
        // glDisable(GL_TEXTURE_2D);

        }
    }
}



