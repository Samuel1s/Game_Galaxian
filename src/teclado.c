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
            if (flag_status_exit == -1) 
            {
                flag_status_exit *= -1;
                glutDisplayFunc(desenhaTelaConfirmacao); 
                glutPostRedisplay();
                break;
            }

        case 'p'://PAUSE 
            flag_status_pause *= -1;
            glutDisplayFunc(desenhaTelaPause);
            glutPostRedisplay();
            break;

         case 'r':
            if (flag_status_reset == 1) 
            {
                if (flag_status_pause == -1) {
                   flag_status_pause *= -1;
                }
                flag_status_reset *= -1;
                flag_status_pause *=-1;

                glutDisplayFunc(desenhaTelaConfirmacao);
                glutPostRedisplay();
                break;
            }
            
        case 'y':
            flag_status_yes *= -1;
            if((flag_status_yes == 1) && (flag_status_exit == 1))
            {
                exit(0);
                break;
            } else {
                if((flag_status_yes == 1) && (flag_status_reset == -1) && (flag_status_exit != 1))
                {
                    posicao_heroi_x = 50.0;
                    flag_status_start *= -1;
                    glutDisplayFunc(desenhaMinhaCena);
                    glutPostRedisplay();
                    flag_status_yes *=(-1);
                    flag_status_reset *=-(1);
                    break;
                }
            }

        case 'n':
            if((flag_status_no == 1) && ((flag_status_exit == 1) || (flag_status_reset == -1)))
            {
                if(flag_status_exit == 1)
                {
                    flag_status_exit *=-1;
                    flag_status_pause =-1;

                }
                if(flag_status_reset == -1)
                {
                    flag_status_reset *=-1;
                }
                glutDisplayFunc(desenhaMinhaCena);
                glutPostRedisplay();
                break;
            }
            
        case 13: //tecla ENTER
            flag_status_start = -1; 
            flag_status_pause *= -1;
            glutPostRedisplay();
            break;

        case 32: // Tecla "ESPAÇO"
            if (flag_status_pause == 1) {
               break;
            }
            flag_controle_missil = 1; //APERTOU A TECLA DE ESPAÇO
            glutDisplayFunc(desenhaMinhaCena);
            glutPostRedisplay();
            break;
        
        case 'd':
            if (flag_status_pause == 1) {
                break;
            }
            if(posicao_heroi_x < gl_world_end_x - (dim_x_nave_heroi/2.0))// Limite a direita.
            {
                posicao_heroi_x+=2;
            }
            glutPostRedisplay();
            break;

        case 'a':
            if (flag_status_pause == 1) {
               break;
            }
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
        if (flag_status_pause == 1) {
            break;
        }
        if(posicao_heroi_x < gl_world_end_x - (dim_x_nave_heroi/2.0))// Limite a direita.
        {
            posicao_heroi_x+=2;
        }
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        if (flag_status_pause == 1) {
            break;
        }
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