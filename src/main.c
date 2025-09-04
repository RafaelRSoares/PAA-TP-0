#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arte.h"

int main() {
    srand(time(NULL));

    int tipo, qtd;
    char opcao;

    printf("PROGRAMA GERADOR DE OBRA DE ARTE:\n");
    printf("=================================\n");
    printf("Escolha o tipo de figura basica a ser usada para criar a obra:\n");
    printf("1 - asterisco simples.\n");
    printf("2 - simbolo de soma com asteriscos.\n");
    printf("3 - letra X com asteriscos.\n");
    printf("4 - figuras aleatorias.\n");
    printf("5 - opcao de obra de arte criada pelo aluno. Ela eh mais legal, recomendo.\n");
    printf("6 - opcao bonus. Homenagem a algo iconico, haha. XD\n");

    printf("Digite o tipo de figura basica desejada: ");
    scanf("%d", &tipo);

    if (tipo == FIGURA_RICKROLL) {
        printf("Digite a quantidade de ciclos (menor ou igual a zero para aleatorio): ");
    } else {
        printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
    }
    scanf("%d", &qtd);

    //opçao 5
    if (tipo == FIGURA_CUSTOM) {
        if (qtd <= 0) qtd = (rand() % 20) + 1;
        if (qtd > 20) qtd = 20;
        jogarBeerPong(qtd);
        return 0;
    }

    //opção 6 heheh
    if (tipo == FIGURA_RICKROLL) {
        if (qtd <= 0) qtd = (rand() % 11) + 5; // entre 5 e 15 ciclos
        if (qtd > 20) qtd = 20;
        jogarRickroll(qtd);
        return 0;
    }

    if (qtd <= 0) qtd = (rand() % 100) + 1;
    if (qtd > 100) qtd = 100;

    do {
        Quadro q;
        inicializarQuadro(&q);

        for (int i = 0; i < qtd; i++) {
            int figura = tipo;

            if (tipo == FIGURA_RANDOM) {
                figura = (rand() % 3) + 1; // 1 a 3
            }

            int linha, coluna;
            int tentativas = 0;
            do {
                linha = (rand() % (LINHAS - 2)) + 1;   // evita borda na linha
                coluna = (rand() % (COLUNAS - 2)) + 1; //      ||     na coluna
                tentativas++;
            } while (!posicaoValida(&q, linha, coluna, figura) && tentativas < 1000);

            if (tentativas < 1000) {
                desenharFigura(&q, linha, coluna, figura);
            }
        }

        imprimirQuadro(&q);

        printf("Deseja gerar um novo quadro com os mesmos valores? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    return 0;
}
