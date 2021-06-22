typedef struct Vetor_2d
{
    float x, y;

}; 

typedef struct Avatar
{
    int status_flag;
    Vetor_2d posicao;
    Vetor_2d dimensao;

};

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