#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100
#define MAX_MISSOES 3

// Estrutura que representa um territorio
typedef struct {
    char nome[TAM_STRING];
    int dono; // 0 = neutro, 1 = jogador, 2 = inimigo
} Territorio;

// Funcao para inicializar os territorios
void inicializarMapa(Territorio* mapa) {
    char* nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        mapa[i].dono = 0;
    }
}

// Funcao para exibir o mapa
void exibirMapa(Territorio* mapa) {
    printf("\n--- MAPA ---\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d. %s - ", i + 1, mapa[i].nome);
        if (mapa[i].dono == 0)
            printf("Neutro\n");
        else if (mapa[i].dono == 1)
            printf("Jogador\n");
        else
            printf("Inimigo\n");
    }
}

// Funcao para atribuir uma missao aleatoria
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Funcao que verifica se a missao foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int total) {
    // Missao 1: conquistar 3 territorios seguidos
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int cont = 0;
        for (int i = 0; i < total; i++) {
            if (mapa[i].dono == 1) {
                cont++;
                if (cont >= 3)
                    return 1;
            } else {
                cont = 0;
            }
        }
    }

    // Missao 2: conquistar todos os territorios do inimigo
    else if (strcmp(missao, "Conquistar todos os territorios inimigos") == 0) {
        int inimigos = 0;
        for (int i = 0; i < total; i++) {
            if (mapa[i].dono == 2)
                inimigos++;
        }
        if (inimigos == 0)
            return 1;
    }

    // Missao 3: conquistar pelo menos 4 territorios
    else if (strcmp(missao, "Conquistar pelo menos 4 territorios") == 0) {
        int jogador = 0;
        for (int i = 0; i < total; i++) {
            if (mapa[i].dono == 1)
                jogador++;
        }
        if (jogador >= 4)
            return 1;
    }

    return 0; // Missao nao cumprida
}

// Funcao para liberar memoria alocada
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// Funcao principal
int main(void) {
    srand(time(NULL));

    // Aloca memoria dinamicamente
    Territorio* mapa = (Territorio*) malloc(sizeof(Territorio) * MAX_TERRITORIOS);
    char* missao = (char*) malloc(TAM_STRING * sizeof(char));

    if (mapa == NULL || missao == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    inicializarMapa(mapa);

    // Lista de missoes
    char* missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Conquistar todos os territorios inimigos",
        "Conquistar pelo menos 4 territorios"
    };

    // Sorteia uma missao
    atribuirMissao(missao, missoes, MAX_MISSOES);

    printf("=== JOGO DE CONQUISTA DE TERRITORIOS ===\n");
    printf("Sua missao: %s\n", missao);

    int opcao;
    do {
        exibirMapa(mapa);
        printf("\nEscolha uma acao:\n");
        printf("1 - Atacar um territorio\n");
        printf("2 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int alvo;
            printf("Escolha o numero do territorio para atacar (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &alvo);

            if (alvo < 1 || alvo > MAX_TERRITORIOS) {
                printf("Territorio invalido.\n");
                continue;
            }

            alvo--; // ajusta o indice

            if (mapa[alvo].dono == 1) {
                printf("Voce ja controla este territorio!\n");
            } else {
                int resultado = rand() % 2; // 0 = perdeu, 1 = venceu
                if (resultado == 1) {
                    mapa[alvo].dono = 1;
                    printf("Voce conquistou o territorio %s!\n", mapa[alvo].nome);
                } else {
                    mapa[alvo].dono = 2;
                    printf("O inimigo manteve o controle de %s!\n", mapa[alvo].nome);
                }
            }

            // Verifica se o jogador venceu
            if (verificarMissao(missao, mapa, MAX_TERRITORIOS)) {
                printf("\n*** MISSAO CUMPRIDA! ***\n");
                printf("Voce venceu o jogo!\n");
                break;
            }
        }

    } while (opcao != 2);

    liberarMemoria(mapa, missao);
    printf("\nJogo encerrado.\n");
    return 0;
}
