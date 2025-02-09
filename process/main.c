#include <stdio.h>
#include <stdlib.h>

typedef enum { PRONTO, EXECUCAO, ESPERA } EstadoProcesso;
typedef enum { CPU_BOUND, IO_BOUND } TipoProcesso;

typedef struct {
    int id;
    TipoProcesso tipo;
    EstadoProcesso estado;
    int tempo_execucao; // Tempo total necessário
    int tempo_cpu_usado; // Tempo de CPU já utilizado
} Processo;

#define MAX_PROCESSOS 10

Processo processos[MAX_PROCESSOS];
int total_processos = 0;

void criar_processo(TipoProcesso tipo, int tempo_execucao) {
    if (total_processos >= MAX_PROCESSOS) {
        printf("Número máximo de processos atingido!\n");
        return;
    }

    Processo novo_processo = {
        .id = total_processos + 1,
        .tipo = tipo,
        .estado = PRONTO,
        .tempo_execucao = tempo_execucao,
        .tempo_cpu_usado = 0
    };

    processos[total_processos] = novo_processo;
    total_processos++;

    printf("Processo %d criado (Tipo: %s, Tempo de Execução: %d).\n",
           novo_processo.id,
           novo_processo.tipo == CPU_BOUND ? "CPU-bound" : "I/O-bound",
           novo_processo.tempo_execucao);
}

void escalonador(int fatia_tempo) {
    int tempo_total = 0;

    while (1) {
        int todos_finalizados = 1;

        for (int i = 0; i < total_processos; i++) {
            if (processos[i].tempo_cpu_usado < processos[i].tempo_execucao) {
                todos_finalizados = 0;

                processos[i].estado = EXECUCAO;
                printf("Processo %d em execução...\n", processos[i].id);

                // Simula o uso da CPU
                int tempo_usado = (processos[i].tempo_execucao - processos[i].tempo_cpu_usado > fatia_tempo)
                                  ? fatia_tempo
                                  : processos[i].tempo_execucao - processos[i].tempo_cpu_usado;

                processos[i].tempo_cpu_usado += tempo_usado;
                tempo_total += tempo_usado;

                printf("Processo %d usou %d unidades de tempo. Tempo total de CPU: %d\n",
                       processos[i].id, tempo_usado, processos[i].tempo_cpu_usado);

                processos[i].estado = PRONTO;

                if (processos[i].tempo_cpu_usado >= processos[i].tempo_execucao) {
                    printf("Processo %d finalizado.\n", processos[i].id);
                }
            }
        }

        if (todos_finalizados) {
            printf("Todos os processos foram finalizados. Tempo total: %d\n", tempo_total);
            break;
        }
    }
}

int main() {
    // Cria alguns processos
    criar_processo(CPU_BOUND, 10); // Processo CPU-bound que precisa de 10 unidades de tempo
    criar_processo(IO_BOUND, 5);   // Processo I/O-bound que precisa de 5 unidades de tempo

    // Executa o escalonador com uma fatia de tempo de 2 unidades
    escalonador(2);

    return 0;
}