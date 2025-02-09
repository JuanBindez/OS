#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_REGISTRO 50

typedef struct {
    int id;
    char nome[TAM_REGISTRO];
} Registro;

// Função para adicionar um registro ao arquivo
void adicionarRegistro(FILE *arquivo) {
    Registro reg;
    printf("Digite o ID: ");
    scanf("%d", &reg.id);
    printf("Digite o nome: ");
    scanf("%s", reg.nome);

    fseek(arquivo, 0, SEEK_END); // Posiciona no final do arquivo
    fwrite(&reg, sizeof(Registro), 1, arquivo); // Escreve o registro
    printf("Registro adicionado com sucesso!\n");
}

// Função para buscar um registro sequencialmente
void buscarSequencial(FILE *arquivo, int id) {
    Registro reg;
    rewind(arquivo); // Volta ao início do arquivo

    while (fread(&reg, sizeof(Registro), 1, arquivo)) {
        if (reg.id == id) {
            printf("Registro encontrado: ID = %d, Nome = %s\n", reg.id, reg.nome);
            return;
        }
    }
    printf("Registro não encontrado.\n");
}

// Função para buscar um registro diretamente
void buscarDireto(FILE *arquivo, int posicao) {
    Registro reg;
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET); // Posiciona no registro
    if (fread(&reg, sizeof(Registro), 1, arquivo)) {
        printf("Registro encontrado: ID = %d, Nome = %s\n", reg.id, reg.nome);
    } else {
        printf("Registro não encontrado.\n");
    }
}

// Função para criar um índice (em memória)
void criarIndice(FILE *arquivo, int *indice, int *tamanho) {
    Registro reg;
    rewind(arquivo);
    *tamanho = 0;

    while (fread(&reg, sizeof(Registro), 1, arquivo)) {
        indice[reg.id] = ftell(arquivo) / sizeof(Registro) - 1; // Mapeia ID para posição
        (*tamanho)++;
    }
    printf("Índice criado com sucesso!\n");
}

// Função para buscar usando índice
void buscarIndexado(FILE *arquivo, int *indice, int id) {
    if (indice[id] == -1) {
        printf("Registro não encontrado.\n");
    } else {
        buscarDireto(arquivo, indice[id]); // Usa o índice para acessar diretamente
    }
}

int main() {
    FILE *arquivo;
    int opcao, id, posicao;
    int indice[1000]; // Supondo IDs de 0 a 999
    memset(indice, -1, sizeof(indice)); // Inicializa o índice com -1 (não encontrado)
    int tamanhoIndice = 0;

    arquivo = fopen("dados.dat", "rb+");
    if (!arquivo) {
        arquivo = fopen("dados.dat", "wb+"); // Cria o arquivo se não existir
        if (!arquivo) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    while (1) {
        printf("\n1. Adicionar Registro\n");
        printf("2. Buscar Sequencial\n");
        printf("3. Buscar Direto\n");
        printf("4. Criar Índice\n");
        printf("5. Buscar Indexado\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarRegistro(arquivo);
                break;
            case 2:
                printf("Digite o ID para busca sequencial: ");
                scanf("%d", &id);
                buscarSequencial(arquivo, id);
                break;
            case 3:
                printf("Digite a posição para busca direta: ");
                scanf("%d", &posicao);
                buscarDireto(arquivo, posicao);
                break;
            case 4:
                criarIndice(arquivo, indice, &tamanhoIndice);
                break;
            case 5:
                printf("Digite o ID para busca indexada: ");
                scanf("%d", &id);
                buscarIndexado(arquivo, indice, id);
                break;
            case 6:
                fclose(arquivo);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}