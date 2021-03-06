#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/criaHeroi.h"
#include "./library/criaObjetos.h"
#include "./library/variaveisGlobais.h"

void desenhaNaveHeroi(float p_x, float p_y)
{
    nave_heroi = criaObjetos(p_x, p_y, dim_x_nave_heroi, dim_y_nave_heroi);

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tx_Nave_Heroi);

        h_v0.x = -nave_heroi.dimensao.x/2;
        h_v0.y = -nave_heroi.dimensao.y/2;

        h_v1.x = nave_heroi.dimensao.x/2;
        h_v1.y = -nave_heroi.dimensao.y/2;

        h_v2.x = nave_heroi.dimensao.x/2;
        h_v2.y = nave_heroi.dimensao.y/2;

        h_v3.x = -nave_heroi.dimensao.x/2;
        h_v3.y =  nave_heroi.dimensao.y/2;


        glPushMatrix();                 
            glTranslatef(nave_heroi.posicao.x, nave_heroi.posicao.y, 0);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0); glVertex3f(h_v0.x, h_v0.y, 0);
                glTexCoord2f(1, 0); glVertex3f(h_v1.x, h_v1.y, 0);
                glTexCoord2f(1, 1); glVertex3f(h_v2.x, h_v2.y, 0);
                glTexCoord2f(0, 1); glVertex3f(h_v3.x, h_v3.y, 0);
            glEnd();
        glPopMatrix();                  
     
    glDisable(GL_TEXTURE_2D);
}

float fronteiraNaveHeroi()
{
    return nave_heroi.posicao.y +  nave_heroi.dimensao.y/2;
}