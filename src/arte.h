#ifndef ARTE_H
#define ARTE_H

#define LINHAS 20
#define COLUNAS 80
#define FIGURA_RICKROLL 6

// Tipos de figuras
#define FIGURA_ASTERISCO 1
#define FIGURA_SOMA      2
#define FIGURA_X         3
#define FIGURA_RANDOM    4
#define FIGURA_CUSTOM    5 //opão 5, o joguinho (com sorte... se vc estiver lendo isso, deu certo)

// Estrutura do quadro
typedef struct {
    char matriz[LINHAS][COLUNAS];
} Quadro;


void inicializarQuadro(Quadro *q);
void imprimirQuadro(const Quadro *q);
int posicaoValida(const Quadro *q, int linha, int coluna, int tipo);
void desenharFigura(Quadro *q, int linha, int coluna, int tipo);
void jogarBeerPong(int numCopos);
void jogarRickroll(int ciclos);

#endif
