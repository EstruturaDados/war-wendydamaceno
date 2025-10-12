#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Função para exibir o mapa (todos os territórios)
void exibirTerritorios(Territorio *mapa, int total) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < total; i++) {
        printf("\n[%d] Território: %s\n", i, mapa[i].nome);
        printf("    Cor do exército: %s\n", mapa[i].cor);
        printf("    Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n=== Batalha entre %s (atacante) e %s (defensor) ===\n",
           atacante->nome, defensor->nome);

    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;

    printf("%s rola o dado e tira: %d\n", atacante->nome, dado_atacante);
    printf("%s rola o dado e tira: %d\n", defensor->nome, dado_defensor);

    // Resultado da batalha
    if (dado_atacante > dado_defensor) {
        printf("\n🎯 %s venceu a batalha!\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor); // defensor muda de dono
        defensor->tropas = atacante->tropas / 2; // recebe metade das tropas do atacante
        atacante->tropas /= 2; // atacante perde metade das tropas
    } else {
        printf("\n💥 %s resistiu ao ataque!\n", defensor->nome);
        atacante->tropas--; // atacante perde 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0;
    }

    printf("\n--- Estado após o ataque ---\n");
    printf("%s -> Tropas: %d | Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s -> Tropas: %d | Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}

// Função para liberar memória alocada
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); // Inicializa a aleatoriedade dos dados
    int total_territorios;
    int opcao;

    printf("===== DESAFIO WAR - NÍVEL AVENTUREIRO =====\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total_territorios);
    limparBufferEntrada();

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = (Territorio *) calloc(total_territorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Menu principal
    do {
        printf("\n=============================\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Exibir territórios\n");
        printf("3 - Atacar território\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarTerritorios(mapa, total_territorios);
                break;
            case 2:
                exibirTerritorios(mapa, total_territorios);
                break;
            case 3:
                if (total_territorios < 2) {
                    printf("\n⚠️ É necessário ter pelo menos 2 territórios cadastrados!\n");
                    break;
                }

                exibirTerritorios(mapa, total_territorios);
                int atacante, defensor;

                printf("\nEscolha o índice do território atacante: ");
                scanf("%d", &atacante);
                printf("Escolha o índice do território defensor: ");
                scanf("%d", &defensor);
                limparBufferEntrada();

                if (atacante < 0 || atacante >= total_territorios ||
                    defensor < 0 || defensor >= total_territorios ||
                    atacante == defensor) {
                    printf("\n⚠️ Escolhas inválidas! Tente novamente.\n");
                    break;
                }

                if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
                    printf("\n⚠️ Você não pode atacar um território da mesma cor!\n");
                    break;
                }

                atacar(&mapa[atacante], &mapa[defensor]);
                break;

            case 0:
                printf("\nSaindo do jogo... Até logo!\n");
                break;

            default:
                printf("\n⚠️ Opção inválida!\n");
                break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
