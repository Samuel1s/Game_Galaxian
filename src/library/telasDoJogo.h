#ifndef _TELA_PRINCIPAL_H_
#define _TELA_PRINCIPAL_H_

void desenhaFundo(GLuint, int, int, int, int);
void desenhaVidasRestantes(float, float);
void desenhaCoin(float, float);

void hudDisplay();
void desenhaMinhaCena();
void desenhaTelaPause();
void desenhaTelaTutorial();
void desenhaTelaGameOver();
void desenhaTelaVencedor();
void desenhaTelaConfirmacao();

#endif