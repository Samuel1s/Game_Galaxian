#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "./library/criaObjetos.h"

Avatar criaObjetos(float pos_x, float pos_y, float dim_x, float dim_y) 
{
    Avatar new_avatar;
    new_avatar.status_flag = 1;
    new_avatar.posicao.x = pos_x;
    new_avatar.posicao.y = pos_y;
    new_avatar.dimensao.x = dim_x;
    new_avatar.dimensao.y = dim_y;
    
    return new_avatar;
}