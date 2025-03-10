/**
 * @brief Ficheiro que contem as funcoes relacionadas com os parques
 * @file parque.c
 * @author Pedro Nunes ist1109368
 */

#include "funcs.h"

/**
 * Funcao que cria um parque
 * @param nome nome do parque
 * @param capacidade capacidade do parque
 * @param valor15Min valor a pagar por 15 minutos
 * @param valor30Apos1Hora valor a pagar apos 1 hora
 * @param valorMaximoDia valor maximo a pagar por dia
 * @return parque
 */
Parque criarParque(char *nome, int capacidade, float valor15Min,
                   float valor30Apos1Hora, float valorMaximoDia) {
    Parque parque;
    parque.nome = strdup(nome);
    parque.capacidade = capacidade;
    parque.valor15Min = valor15Min;
    parque.valor30Apos1Hora = valor30Apos1Hora;
    parque.valorMaximoDia = valorMaximoDia;
    parque.lugaresOcupados = 0;
    parque.carros = criarCarroHashTable(103);
    parque.carros->size = 103;
    parque.tickets = NULL;
    return parque;
}

/**
 * Funcao que cria um node de parque
 * @param Parque parque
 * @return NodeParque
 */
NodeParque *criarNodeParque(Parque parque) {
    NodeParque *newNode = (NodeParque *)malloc(sizeof(NodeParque));

    newNode->parque = parque;
    newNode->next = NULL;
    return newNode;
}

/**
 * Funcao que adiciona um parque a lista de parques
 * @param **parques lista de parques
 * @param Parque parque a adicionar
 */
void adicionarParque(NodeParque **parques, Parque parque) {
    NodeParque *newNode = criarNodeParque(parque);
    NodeParque *current;

    if (*parques == NULL) {
        *parques = newNode;
    } else {
        current = *parques;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

/**
 * Funcao que trata os erros ao adicionar um parque e mostra os erros
 * @param *parques lista de parques
 * @param Parque parque a adicionar
 * @param numParques numero de parques
 * @return 1 se nao houver erros, 0 se houver erros
 */
int tratarErrosAdicionarParque(NodeParque *parques, Parque parque,
                               int numParques) {
    NodeParque *aux = parques;

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, parque.nome) == 0) {
            printf("%s: parking already exists.\n", parque.nome);
            return 0;
        }
        aux = aux->next;
    }
    if (parque.capacidade <= 0) {
        printf("%d: invalid capacity.\n", parque.capacidade);
        return 0;
    }

    if (parque.valor15Min < 0.0 || parque.valor30Apos1Hora < 0.0 ||
        parque.valorMaximoDia < 0.0 ||
        parque.valor30Apos1Hora < parque.valor15Min ||
        parque.valorMaximoDia < parque.valor30Apos1Hora) {
        printf("invalid cost.\n");
        return 0;
    }

    if (numParques + 1 > MAXPARQUES) {
        printf("too many parks.\n");
        return 0;
    }
    return 1;
}

/**
 * Funcao que imprime os parques
 * @param *parques lista de parques
 */
void imprimeParques(NodeParque *parques) {
    NodeParque *aux = parques;

    while (aux != NULL) {
        printf("%s %d %d\n", aux->parque.nome, aux->parque.capacidade,
               aux->parque.capacidade - aux->parque.lugaresOcupados);
        aux = aux->next;
    }
};

/**
 * Funcao que imprime os nomes dos parques
 * @param **nomes vetor com os nomes dos parques
 * @param numParques numero de parques
 */
void imprimeNomeParques(char **nomes, int numParques) {
    int i;

    for (i = 0; i < numParques - 1; i++) {
        printf("%s\n", nomes[i]);
    }
}

/**
 * Funcao que liberta a memoria alocada de um parque
 * @param Parque parque
 */
void freeParque(Parque parque) {
    free(parque.nome);
    NodeCarro *auxCarros, *nextCarro;
    NodeTicket *auxTickets = parque.tickets;
    NodeTicket *nextTicket;
    int i;

    for (i = 0; i < parque.carros->size; i++) {
        auxCarros = parque.carros->buckets[i];
        while (auxCarros != NULL) {
            nextCarro = auxCarros->next;
            free(auxCarros->carro.Matricula);
            free(auxCarros);
            auxCarros = nextCarro;
        }
    }
    free(parque.carros->buckets);
    free(parque.carros);

    while (auxTickets != NULL) {
        nextTicket = auxTickets->next;
        free(auxTickets->ticket.Matricula);
        free(auxTickets);
        auxTickets = nextTicket;
    }
}

/**
 * Funcao que liberta a memoria alocada de uma lista de parques
 * @param *parques lista de parques
 */
void freeListaParques(NodeParque *parques) {
    NodeParque *aux = parques;
    NodeParque *next;

    while (aux != NULL) {
        next = aux->next;
        freeParque(aux->parque);
        free(aux);
        aux = next;
    }
}

/**
 * Funcao que obtem um vetor com os nomes dos parques
 * @param *parques lista de parques
 * @param numParques numero de parques
 * @return char **nomes
 */
char **obterNomeParques(NodeParque *parques, int numParques) {
    NodeParque *aux = parques;
    char **nomes = malloc(sizeof(char *) * numParques);
    int i = 0;

    while (aux != NULL && i < numParques) {
        nomes[i] = strdup(aux->parque.nome);
        i++;
        aux = aux->next;
    }
    return nomes;
}

/**
 * Funcao que troca duas strings
 * @param **str1 string 1
 * @param **str2 string 2
 */
void trocarStr(char **str1, char **str2) {
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

/**
 * Funcao que ordena os nomes dos parques num vetor
 * @param **nomes vetor com os nomes dos parques
 * @param numParques numero de parques
 */
void ordenarNomesParques(char **nomes, int numParques) {
    int i, j;

    for (i = 0; i < numParques - 1; i++) {
        for (j = 0; j < numParques - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                trocarStr(&nomes[j], &nomes[j + 1]);
            }
        }
    }
}

/**
 * Funcao que trata os erros ao remover um parque e mostra os erros
 * @param *parques lista de parques
 * @param *nomeParque nome do parque a remover
 * @return 1 se nao houver erros, 0 se houver erros
 */
int tratarErrosRemoverParque(NodeParque *parques, char *nomeParque) {
    NodeParque *aux = parques;

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            return 1;
        }
        aux = aux->next;
    }
    printf("%s: no such parking.\n", nomeParque);
    return 0;
}

/**
 * Funcao que remove um parque da lista de parques, e liberta a memoria alocada
 * para o Parque
 * @param **parques lista de parques
 * @param *nomeParque nome do parque a remover
 * @param numParques numero de parques
 */
void removerParque(NodeParque **parques, char *nomeParque, int numParques) {
    NodeParque *aux = *parques;
    NodeParque *prev = NULL;
    char **nomesParques;

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            if (prev == NULL) {
                *parques = aux->next;
            } else {
                prev->next = aux->next;
            }
            freeParque(aux->parque);
            free(aux);
            break;
        }
        prev = aux;
        aux = aux->next;
    }

    nomesParques = obterNomeParques(*parques, numParques);
    ordenarNomesParques(nomesParques, numParques - 1);
    imprimeNomeParques(nomesParques, numParques);

    for (int i = 0; i < numParques - 1; i++) {
        free(nomesParques[i]);
    }
    free(nomesParques);
}
