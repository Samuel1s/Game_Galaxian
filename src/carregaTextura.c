#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <GL/freeglut.h>

#include "./library/variaveisGlobais.h"

GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(arquivo, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

void inicializaTextura() {

    // Habilita mesclagem de cores, para termos textura com transparência.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    tx_Nave_Heroi = carregaTextura("../imgs/nave_heroi.png");
	tx_Nave_Inimiga = carregaTextura("../imgs/nave_inimiga.png");
    tx_Fundo_Jogo = carregaTextura("../imgs/fundo_teste.png");
    tx_Fundo_Tutorial = carregaTextura("../imgs/fundo_tutorial.png");
    tx_Desenho_Space = carregaTextura("../imgs/space_bar.png");
    tx_Desenho_Enter = carregaTextura("../imgs/enter_key.png");
    tx_Desenho_Arrows = carregaTextura("../imgs/arrows_keys.png");
    tx_Desenho_A_D = carregaTextura("../imgs/letter_a_d.png");
    tx_Desenho_Mouse = carregaTextura("../imgs/mouse.png");
    tx_Desenho_Vida = carregaTextura("../imgs/heart.png");
    tx_Desenho_Coin = carregaTextura("../imgs/coin.png");
        
}