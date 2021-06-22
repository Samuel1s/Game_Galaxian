#ifndef _CRIA_OBJETOS_H_
#define _CRIA_OBJETOS_H_

typedef struct cria_vetor_2d
{
    float x, y;

} Vetor_2d;

typedef struct avatar
{
    int status_flag;
    Vetor_2d posicao;
    Vetor_2d dimensao;

} Avatar;

Avatar criaObjetos(float, float, float, float);

#endif 