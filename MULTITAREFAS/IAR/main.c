#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
void tarefa_4(void);
void tarefa_5(void);
void tarefa_6(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_5[TAM_PILHA_5];
uint32_t PILHA_TAREFA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/* Declaração das variáveis Globais */
volatile uint16_t buff[5] = {0, 0, 0, 0, 0};

/* Declaração de Semáforos */ // a funcao vai executar qdo contador > 0
semaforo_t sem1 = {1,0};
semaforo_t sem2 = {0,0};
semaforo_t sem3 = {0,0};
semaforo_t sem4 = {0,0};
semaforo_t sem5 = {0,0};
/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{        
         
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 5);
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 4);
        
        CriaTarefa(tarefa_3, "Tarefa 3", PILHA_TAREFA_3, TAM_PILHA_3, 3);
        
        CriaTarefa(tarefa_4, "Tarefa 4", PILHA_TAREFA_4, TAM_PILHA_4, 2);
	
	CriaTarefa(tarefa_5, "Tarefa 5", PILHA_TAREFA_5, TAM_PILHA_5, 1);
        
        CriaTarefa(tarefa_6, "Tarefa 6", PILHA_TAREFA_6, TAM_PILHA_6, 6 );
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}


/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_1(void)
{
	volatile uint16_t cnt1 = 0;
	for(;;)
	{
                SemaforoAguarda(&sem2);
		cnt1++;
                buff[0] = cnt1;
                SemaforoLibera(&sem1);
	}
}

void tarefa_2(void)
{       
	volatile uint16_t cnt2 = 0;
	for(;;)
	{
                SemaforoAguarda(&sem3);
		cnt2++;
                buff[1] = cnt2;
                SemaforoLibera(&sem2);
	}
}

void tarefa_3(void)
{
	volatile uint16_t cnt3 = 0;
	for(;;)
	{
                SemaforoAguarda(&sem4);
		cnt3++;
                buff[2] = cnt3;
                SemaforoLibera(&sem3);
	}
}

void tarefa_4(void)
{
	volatile uint16_t cnt4 = 0;
	for(;;)
	{
                SemaforoAguarda(&sem5);
		cnt4++;
                buff[3] = cnt4;
                SemaforoLibera(&sem4);
	}
}

void tarefa_5(void)
{
	volatile uint16_t cnt5 = 0;
	for(;;)
	{
                SemaforoAguarda(&sem1);
		cnt5++;
                buff[4] = cnt5;
                SemaforoLibera(&sem5);
	}
}

void tarefa_6(void)
{
	volatile uint16_t cnt6 = 0;
        volatile uint16_t i  = 1;
        uint16_t soma =0;
	for(;;)
	{
          if(i == 1){
            i = 0;
            TarefaEspera(30);
          }
          else{
            for(i=0; i<5; i++){
		soma = soma + buff[i];
            }
            //printf("%" PRIu16 "\n", soma);
            soma = i = 0;
            TarefaEspera(30);
          }
	}
}
