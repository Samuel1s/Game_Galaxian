#include <stdio.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "./library/variaveisGlobais.h"


void inicializarMusica()
{
    SDL_Init( SDL_INIT_AUDIO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ); //- inicializa SDL_Mixer
    atexit(Mix_CloseAudio);
}

void carregarMusica()
{
    musica_jogo = Mix_LoadMUS("../musics/space-ambience.mp3");
    musica_vencedor = Mix_LoadMUS("../musics/space-heroes.mp3");
}