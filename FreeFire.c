#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// 1. Criação da Struct (O Bloco de Construção)
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void lerString(char *buffer, int tamanho);
void mostrarComponentes(Componente vetor[], int qtd);
void bubbleSortNome(Componente vetor[], int qtd);
void insertionSortTipo(Componente vetor[], int qtd);
void selectionSortPrioridade(Componente vetor[], int qtd);
int buscaBinariaPorNome(Componente vetor[], int qtd, char chave[]);

int main() {
    Componente torre[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0; // Flag de segurança para a busca binária

    printf("=== SISTEMA DE ESCAPE DA ILHA: MÓDULO DA TORRE ===\n");
    printf("Quantos componentes voce recuperou (max %d)? ", MAX_COMPONENTES);
    scanf("%d", &qtd);
    getchar(); // Limpar o buffer do teclado

    if (qtd > MAX_COMPONENTES) qtd = MAX_COMPONENTES;

    // 2. Entrada de Dados
    for (int i = 0; i < qtd; i++) {
        printf("\nConfigurando Componente #%d:\n", i + 1);
        printf("Nome (ex: Chip, Antena): ");
        lerString(torre[i].nome, 30);
        printf("Tipo (ex: Controle, Suporte): ");
        lerString(torre[i].tipo, 20);
        printf("Prioridade (1-10): ");
        scanf("%d", &torre[i].prioridade);
        getchar(); // Limpar buffer
    }

    do {
        printf("\n--- PAINEL ESTRATEGICO ---\n");
        printf("1. Visualizar Componentes\n");
        printf("2. Ordenar por NOME (Bubble Sort) -> Prepara para Busca\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Buscar Item-Chave (Busca Binaria)\n");
        printf("0. Finalizar Missao\n");
        printf("Escolha sua estrategia: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                mostrarComponentes(torre, qtd);
                break;
            case 2:
                bubbleSortNome(torre, qtd);
                ordenadoPorNome = 1; // Agora a busca binária é segura
                printf("\n[SISTEMA] Ordenacao concluida. Busca Binaria desbloqueada!\n");
                break;
            case 3:
                insertionSortTipo(torre, qtd);
                ordenadoPorNome = 0; // A ordem alfabética foi quebrada
                break;
            case 4:
                selectionSortPrioridade(torre, qtd);
                ordenadoPorNome = 0; // A ordem alfabética foi quebrada
                break;
            case 5:
                if (ordenadoPorNome) {
                    char chave[30];
                    printf("Digite o nome do componente-chave: ");
                    lerString(chave, 30);
                    int pos = buscaBinariaPorNome(torre, qtd, chave);
                    if (pos != -1) {
                        printf("\n[SUCESSO] Componente '%s' encontrado na posicao %d! Ativando torre...\n", chave, pos + 1);
                    } else {
                        printf("\n[ERRO] Componente '%s' nao encontrado nos destrocos.\n", chave);
                    }
                } else {
                    printf("\n[ALERTA] A busca binaria exige ordenacao por NOME primeiro (Opcao 2).\n");
                }
                break;
            case 0:
                printf("Saindo do sistema... Boa sorte na fuga!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Função auxiliar para ler strings e remover o \n do final
void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void mostrarComponentes(Componente vetor[], int qtd) {
    printf("\n%-30s | %-20s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("%-30s | %-20s | %d\n", vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// 3. Bubble Sort: Ordena por NOME
void bubbleSortNome(Componente vetor[], int qtd) {
    long comparacoes = 0;
    clock_t inicio = clock(); // Inicia cronômetro

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock(); // Para cronômetro
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n[METRICAS BUBBLE SORT]\nComparacoes: %ld\nTempo: %f segundos\n", comparacoes, tempo_gasto);
}

// 3. Insertion Sort: Ordena por TIPO
void insertionSortTipo(Componente vetor[], int qtd) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < qtd; i++) {
        Componente pivo = vetor[i];
        int j = i - 1;
        
        // Loop interno do insertion
        while (j >= 0) {
            comparacoes++;
            if (strcmp(vetor[j].tipo, pivo.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break; 
            }
        }
        vetor[j + 1] = pivo;
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n[METRICAS INSERTION SORT]\nComparacoes: %ld\nTempo: %f segundos\n", comparacoes, tempo_gasto);
}

// 3. Selection Sort: Ordena por PRIORIDADE
void selectionSortPrioridade(Componente vetor[], int qtd) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < qtd - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < qtd; j++) {
            comparacoes++;
            // Ordenando do menor para o maior (pode inverter o sinal para maior prioridade primeiro)
            if (vetor[j].prioridade < vetor[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            Componente temp = vetor[i];
            vetor[i] = vetor[indiceMenor];
            vetor[indiceMenor] = temp;
        }
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n[METRICAS SELECTION SORT]\nComparacoes: %ld\nTempo: %f segundos\n", comparacoes, tempo_gasto);
}

// 4. Busca Binária
int buscaBinariaPorNome(Componente vetor[], int qtd, char chave[]) {
    int inicio = 0;
    int fim = qtd - 1;
    int comparacoes_busca = 0;

    printf("\n[BUSCA BINARIA] Iniciando varredura...\n");

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes_busca++;
        
        int resultado = strcmp(vetor[meio].nome, chave);

        if (resultado == 0) {
            printf("Comparacoes na busca: %d\n", comparacoes_busca);
            return meio; // Encontrou
        }
        if (resultado < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    printf("Comparacoes na busca: %d\n", comparacoes_busca);
    return -1; // Não encontrou
}