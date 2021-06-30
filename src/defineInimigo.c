#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/teclado.h"
#include "./library/criaHeroi.h" 
#include "./library/criaInimigo.h"
#include "./library/criaObjetos.h"
#include "./library/variaveisGlobais.h"

void criandoInimigos() {
    float p_y = pos_y_nave_inimiga;
    for (int i = 0; i < M_I; i++)
    {
        float p_x = pos_x_nave_inimiga;
        for (int j = 0; j  <  M_J; j++)
        {
            naves_inimigas[i][j] = criaObjetos(p_x, p_y, dim_x_nave_inimiga, dim_y_nave_inimiga);
            p_x += pos_x_nave_inimiga;  
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
                teclaPressionada(27, 1, 1); // Provisorio - Sera a de Tela Vencedor.
           }

           if (naves_inimigas[i][j].status_flag == 1)
           {
                if (naves_inimigas[i][j].posicao.y < (fronteiraNaveHeroi()))
                {
                    teclaPressionada(27, 1, 1); // Provisorio - Sera a de Tela game over.
                }
           }
           

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tx_Nave_Inimiga);

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
        
        glDisable(GL_TEXTURE_2D);
        }
    }
}



