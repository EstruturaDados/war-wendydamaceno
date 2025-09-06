#include <stdio.h> //Biblioteca para entrada e saída de dados.

#include <stdlib.h> //Biblioteca para funções gerais (memória, aleatório, sair do programa).

#include <string.h> //Biblioteca para manipulação de textos (strings).

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

// Definição da estrutura
struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int tropas;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio mapa[MAX_TERRITORIOS];
    int total_territorios = 0;
    int opcao;

    do {
        printf("\n=============================\n");
        printf("   DESAFIO WAR - NÍVEL NOVATO\n");
        printf("=============================\n");
        printf("1 - Cadastrar território\n");
        printf("2 - Listar territórios\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                if (total_territorios < MAX_TERRITORIOS) {
                    printf("\n--- Cadastro de Território ---\n");
                    
                    printf("Digite o nome do território: ");
                    fgets(mapa[total_territorios].nome, TAM_STRING, stdin);
                    mapa[total_territorios].nome[strcspn(mapa[total_territorios].nome, "\n")] = 0;

                    printf("Digite a cor do exército: ");
                    fgets(mapa[total_territorios].corExercito, TAM_STRING, stdin);
                    mapa[total_territorios].corExercito[strcspn(mapa[total_territorios].corExercito, "\n")] = 0;

                    printf("Digite o número de tropas: ");
                    scanf("%d", &mapa[total_territorios].tropas);
                    limparBufferEntrada();

                    total_territorios++;
                    printf("\nTerritório cadastrado com sucesso!\n");
                } else {
                    printf("\n⚠️ Limite de territórios atingido (%d).\n", MAX_TERRITORIOS);
                }
                break;

            case 2:
                printf("\n--- Estado Atual do Mapa ---\n");
                if (total_territorios == 0) {
                    printf("Nenhum território cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < total_territorios; i++) {
                        printf("\nTerritório %d:\n", i + 1);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Exército: %s\n", mapa[i].corExercito);
                        printf("Tropas: %d\n", mapa[i].tropas);
                    }
                }
                break;

            case 0:
                printf("\nSaindo do jogo... Até mais!\n");
                break;

            default:
                printf("\n⚠️ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}