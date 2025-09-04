#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //usleep
#include <time.h>
#include "arte.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void esperar(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Inicializa o quadro
void inicializarQuadro(Quadro *q) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == 0 || i == LINHAS - 1) {
                q->matriz[i][j] = '-';
            } else if (j == 0 || j == COLUNAS - 1) {
                q->matriz[i][j] = '|';
            } else {
                q->matriz[i][j] = ' ';
            }
        }
    }
}

// Imprime o quadro (os nomes das funções estão bem óbvios já, vou parar)
void imprimirQuadro(const Quadro *q) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            putchar(q->matriz[i][j]);
        }
        putchar('\n');
    }
}

// Vê se é possível colocar figura na posição
int posicaoValida(const Quadro *q, int linha, int coluna, int tipo) {
    // olha se a figura cabe dentro do quadro
    if (tipo == FIGURA_ASTERISCO) {
        return (q->matriz[linha][coluna] == ' ');
    }
    else if (tipo == FIGURA_SOMA) {
        if (linha <= 0 || linha >= LINHAS - 1 ||
            coluna <= 0 || coluna >= COLUNAS - 1) return 0;

        return (q->matriz[linha][coluna] == ' ' &&
                q->matriz[linha-1][coluna] == ' ' &&
                q->matriz[linha+1][coluna] == ' ' &&
                q->matriz[linha][coluna-1] == ' ' &&
                q->matriz[linha][coluna+1] == ' ');
    }
    else if (tipo == FIGURA_X) {
        if (linha <= 0 || linha >= LINHAS - 1 ||
            coluna <= 0 || coluna >= COLUNAS - 1) return 0;

        return (q->matriz[linha][coluna] == ' ' &&
                q->matriz[linha-1][coluna-1] == ' ' &&
                q->matriz[linha-1][coluna+1] == ' ' &&
                q->matriz[linha+1][coluna-1] == ' ' &&
                q->matriz[linha+1][coluna+1] == ' ');
    }
    return 0;
}


void desenharFigura(Quadro *q, int linha, int coluna, int tipo) {
    if (tipo == FIGURA_ASTERISCO) {
        q->matriz[linha][coluna] = '*';
    }
    else if (tipo == FIGURA_SOMA) {
        q->matriz[linha][coluna] = '*';
        q->matriz[linha-1][coluna] = '*';
        q->matriz[linha+1][coluna] = '*';
        q->matriz[linha][coluna-1] = '*';
        q->matriz[linha][coluna+1] = '*';
    }
    else if (tipo == FIGURA_X) {
        q->matriz[linha][coluna] = '*';
        q->matriz[linha-1][coluna-1] = '*';
        q->matriz[linha-1][coluna+1] = '*';
        q->matriz[linha+1][coluna-1] = '*';
        q->matriz[linha+1][coluna+1] = '*';
    }
    else if (tipo == FIGURA_CUSTOM) {

    }
}

// Implementação da opção 5: Beer Pong
void jogarBeerPong(int numCopos) {
    Quadro q;
    inicializarQuadro(&q);

    int coposRestantes = numCopos;

    //copos na linha 2
    for (int i = 0; i < numCopos; i++) {
        int col;
        do {
            col = (rand() % (COLUNAS - 2)) + 1;
        } while (q.matriz[2][col] != ' ');
        q.matriz[2][col] = 'O';
    }
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        imprimirQuadro(&q);
        printf("Obs. (o) signfica que essa coluna nao tem um copo.\n Escolha a coluna para jogar a bolinha (1-%d):", COLUNAS-2);
        int col;
        scanf("%d", &col);
        if (col < 1) col = 1;
        if (col > COLUNAS-2) col = COLUNAS-2;

        int acertou = 0;
        for (int lin = 1; lin < LINHAS-1; lin++) {
            if (q.matriz[lin][col] == 'O') {
                q.matriz[lin][col] = '*';
                acertou = 1;
                coposRestantes--;
                break;
            }
        }

        if (acertou) {
            printf("Caiu em um copo\n");
        } else {
            q.matriz[LINHAS-2][col] = 'o';
            printf("Errou...\n");
        }

        if (coposRestantes == 0) {
            imprimirQuadro(&q);
            printf("Parabens! Você derrubou todos os copos!\n");
            break;
        }

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &continuar);
    }
}

// -------------------
// Rickroll (OPÇÃO BÔNUS!!!)
// -------------------

void desenharRick(Quadro *q, int linha, int coluna, int frame) {
    //5 frames do Rick
    const char *rick[5][4] = {

        { "  O  ", " /|\\ ", "  |  ", " / \\ " }, // Frame A: braços para cima
        { "  O  ", " \\|/ ", "  |  ", " / \\ " }, // Frame B: braços "cruzados"
        { "  O/ ", " /| ", "  |  ", " / \\ " }, // Frame C: braço direito levantado
        { " \\O  ", "  |\\ ", "  |  ", " / \\ " }, // Frame D: braço esquerdo levantado
        { "  O  ", " -|- ", "  |  ", " / \\ " }  // Frame E: braços para os lados
    };

    for (int i = 0; i < 4; i++) {
        int c = coluna;
        for (int j = 0; rick[frame][i][j] != '\0'; j++) {
            if (linha+i < LINHAS-1 && c+j < COLUNAS-1) {
                q->matriz[linha+i][c+j] = rick[frame][i][j];
            }
        }
    }
}

void jogarRickroll(int ciclos) {
    srand(time(NULL));

    int numRicks = (rand() % 4) + 2;
    int colunas[5];
    int linhas[5];

    for (int i = 0; i < numRicks; i++) {
        int col, lin;
        int valido;
        do {
            valido = 1;
            col = (rand() % (COLUNAS - 10)) + 2;
            lin = (rand() % (LINHAS - 8)) + 2;
            for (int j = 0; j < i; j++) {
                if (abs(col - colunas[j]) < 6 || abs(lin - linhas[j]) < 4) {
                    valido = 0;
                    break;
                }
            }
        } while (!valido);
        colunas[i] = col;
        linhas[i] = lin;
    }

    for (int ciclo = 0; ciclo < ciclos; ciclo++) {
        for (int frame = 0; frame < 5; frame++) {
            Quadro q;
            inicializarQuadro(&q);

            for (int i = 0; i < numRicks; i++) {
                desenharRick(&q, linhas[i], colunas[i], frame);
            }

            imprimirQuadro(&q);
            esperar(200); // 0.2s
            limparTela();
        }
    }

    printf("Never gonna give you up...\nNever gonna let you down...\nNever gonna run around and desert you!\n");
}