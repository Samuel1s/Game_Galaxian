#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./library/teclado.h"
#include "./library/criaMisseis.h"
#include "./library/atualizaJogo.h"
#include "./library/telaPrincipal.h"
#include "./library/variaveisGlobais.h"

void teclaPressionada(unsigned char key, int x, int y)
{
    // ve qual tecla foi pressionada
    switch(key)
    {
        case 27:      // Tecla "ESC"
            exit(0);  // Sai da aplicacao
            break;
        
        case 32: // Tecla "ESPAÇO"
            flag_controle_missil = 1; //APERTOU A TECLA DE ESPAÇO
            glutDisplayFunc(desenhaMinhaCena);
            glutPostRedisplay();
            break;
        
        case 'd':
            if(posicao_heroi_x < gl_world_end_x - (dim_x_nave_heroi/2.0))// Limite a direita.
            {
                posicao_heroi_x+=2;
            }
            glutPostRedisplay();
            break;

        case 'a':
            if(posicao_heroi_x > gl_world_begin_x + (dim_x_nave_heroi/2.0)) // Limite a esquerda.
            {
                posicao_heroi_x-=2;
            }
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

void teclaEspecialPressionada(int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_RIGHT:
        if(posicao_heroi_x < gl_world_end_x - (dim_x_nave_heroi/2.0))// Limite a direita.
        {
            posicao_heroi_x+=2;
        }
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        if(posicao_heroi_x > gl_world_begin_x + (dim_x_nave_heroi/2.0)) // Limite a esquerda.
        {
            posicao_heroi_x-=2;
        }
        glutPostRedisplay();
        break;
    
    default:
        break;
  }
}