/**
 * @brief Ficheiro que contem as funcoes relacionadas com os carros
 * @file carro.c
 * @author Pedro Nunes ist1109368
 */

#include "funcs.h"

/**
 * Funcao que cria um carro
 * @param matricula matricula do carro
 * @param dataEntrada data de entrada do carro
 * @param horaEntrada hora de entrada do carro
 * @return carro
 */
Carro criarCarro(char *matricula, Data dataEntrada, Hora horaEntrda) {
    Carro carro;
    carro.Matricula = strdup(matricula);
    carro.dataEntrada = dataEntrada;
    carro.horaEntrada = horaEntrda;
    carro.estado = DENTRO;
    return carro;
}

/**
 * Funcao que cria um node de carro
 * @param Carro carro
 * @return NodeCarro
 */
NodeCarro *criarNodeCarro(Carro carro) {
    NodeCarro *newNode = (NodeCarro *)malloc(sizeof(NodeCarro));

    newNode->carro = carro;
    newNode->next = NULL;
    return newNode;
}
/**
 * Funcao que calcula o hash de uma string
 * @param str string a ser calculado o hash
 * @param size tamanho da hashtable
 * @return hash da string
 */
unsigned long hash(char *str, int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // o mesmo que hash * 33 + c
    }

    return hash % size;
}

/**
 * Funcao que cria uma hashtable de carros
 * @param size tamanho da hashtable
 * @return hashtable de carros
 */
CarroHashTable *criarCarroHashTable(int size) {
    CarroHashTable *carros = malloc(sizeof(CarroHashTable));
    carros->size = size;
    carros->buckets = malloc(sizeof(NodeCarro *) * size);
    for (int i = 0; i < size; i++) {
        carros->buckets[i] = NULL;
    }
    return carros;
}

/**
 * Funcao que adiciona um carro a um parque
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @param carro carro a adicionar
 */
void adicionarCarro(NodeParque **parques, char *nomeParque, Carro carro) {
    NodeParque *auxParque = *parques;
    NodeCarro *newNodeCarro = criarNodeCarro(carro);
    NodeCarro *current;
    unsigned long index;

    while (auxParque != NULL) {
        if (strcmp(auxParque->parque.nome, nomeParque) == 0) {
            index = hash(carro.Matricula, auxParque->parque.carros->size);

            if (auxParque->parque.carros->buckets[index] == NULL) {
                auxParque->parque.carros->buckets[index] = newNodeCarro;
            } else {
                current = auxParque->parque.carros->buckets[index];
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNodeCarro;
            }
            break;
        }
        auxParque = auxParque->next;
    }

    auxParque->parque.lugaresOcupados++;
    printf("%s %d\n", auxParque->parque.nome,
           auxParque->parque.capacidade - auxParque->parque.lugaresOcupados);
}

/**
 * Funcao que remove um carro de um parque
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @param matricula matricula do carro
 * @param data data de saida do carro
 * @param hora hora de saida do carro
 */
void removerCarro(NodeParque **parques, char *nomeParque, char *matricula,
                  Data data, Hora hora) {
    NodeParque *auxParque = *parques;
    CarroHashTable *carros;
    unsigned long index;
    NodeCarro *auxNodeCarro;
    Ticket ticket;
    float valorPago;

    while (auxParque != NULL) {
        if (strcmp(auxParque->parque.nome, nomeParque) == 0) {
            carros = auxParque->parque.carros;
            index = hash(matricula, carros->size);
            auxNodeCarro = carros->buckets[index];

            while (auxNodeCarro != NULL) {
                if (strcmp(auxNodeCarro->carro.Matricula, matricula) == 0 &&
                    auxNodeCarro->carro.estado == DENTRO) {
                    auxNodeCarro->carro.estado = FORA;
                    auxNodeCarro->carro.dataSaida = data;
                    auxNodeCarro->carro.horaSaida = hora;
                    auxParque->parque.lugaresOcupados--;
                    valorPago = faturar(auxNodeCarro->carro.dataEntrada,
                                        auxNodeCarro->carro.horaEntrada, data,
                                        hora, auxParque->parque.valor15Min,
                                        auxParque->parque.valor30Apos1Hora,
                                        auxParque->parque.valorMaximoDia);
                    ticket = criarTicket(matricula, data, hora, valorPago);
                    adicionarTicket(&auxParque->parque.tickets, ticket);
                    auxNodeCarro->carro.valorPago = valorPago;

                    printf(
                        "%s %02d-%02d-%d %02d:%02d %02d-%02d-%d "
                        "%02d:%02d "
                        "%0.2f\n",
                        matricula, auxNodeCarro->carro.dataEntrada.dia,
                        auxNodeCarro->carro.dataEntrada.mes,
                        auxNodeCarro->carro.dataEntrada.ano,
                        auxNodeCarro->carro.horaEntrada.hora,
                        auxNodeCarro->carro.horaEntrada.minuto, data.dia,
                        data.mes, data.ano, hora.hora, hora.minuto, valorPago);
                    break;
                }
                auxNodeCarro = auxNodeCarro->next;
            }
            break;
        }
        auxParque = auxParque->next;
    }
}

/**
 * Funcao que imprime as entradas e saidas de um carro em todos os parques
 * @param parques lista de parques
 * @param matricula matricula do carro
 * @param numParques numero de parques
 */
void listarEntradasSaidas(NodeParque *parques, char *matricula,
                          int numParques) {
    char **nomeParques = obterNomeParques(parques, numParques);
    NodeParque *auxParque;
    NodeCarro *auxNodeCarro;
    int i;
    unsigned long index;

    ordenarNomesParques(nomeParques, numParques);

    for (i = 0; i < numParques; i++) {
        auxParque = parques;

        while (auxParque != NULL) {
            if (strcmp(auxParque->parque.nome, nomeParques[i]) == 0) {
                index = hash(matricula, auxParque->parque.carros->size);

                auxNodeCarro = auxParque->parque.carros->buckets[index];

                while (auxNodeCarro != NULL) {
                    if (strcmp(auxNodeCarro->carro.Matricula, matricula) == 0) {
                        if (auxNodeCarro->carro.estado == DENTRO) {
                            printf("%s %02d-%02d-%d %02d:%02d\n",
                                   auxParque->parque.nome,
                                   auxNodeCarro->carro.dataEntrada.dia,
                                   auxNodeCarro->carro.dataEntrada.mes,
                                   auxNodeCarro->carro.dataEntrada.ano,
                                   auxNodeCarro->carro.horaEntrada.hora,
                                   auxNodeCarro->carro.horaEntrada.minuto);
                        } else {
                            printf(
                                "%s %02d-%02d-%d %02d:%02d "
                                "%02d-%02d-%d "
                                "%02d:%02d\n",
                                auxParque->parque.nome,
                                auxNodeCarro->carro.dataEntrada.dia,
                                auxNodeCarro->carro.dataEntrada.mes,
                                auxNodeCarro->carro.dataEntrada.ano,
                                auxNodeCarro->carro.horaEntrada.hora,
                                auxNodeCarro->carro.horaEntrada.minuto,
                                auxNodeCarro->carro.dataSaida.dia,
                                auxNodeCarro->carro.dataSaida.mes,
                                auxNodeCarro->carro.dataSaida.ano,
                                auxNodeCarro->carro.horaSaida.hora,
                                auxNodeCarro->carro.horaSaida.minuto);
                        }
                    }
                    auxNodeCarro = auxNodeCarro->next;
                }
            }
            auxParque = auxParque->next;
        }
    }
    for (int i = 0; i < numParques; i++) {
        free(nomeParques[i]);
    }
    free(nomeParques);
}

/**
 * Funcao que verifica se uma matricula eh valida
 * @param matricula matricula a verificar
 * @return 1 se a matricula eh valida, 0 caso contrario
 */
int matriculaValida(char *matricula) {
    int i = 0, r = 0;

    for (i = 0; i < 3; i++) {
        r += (('0' <= matricula[2 * i + i] && matricula[2 * i + i] <= '9' &&
               '0' <= matricula[2 * i + i + 1] &&
               matricula[2 * i + i + 1] <= '9') -
              ('A' <= matricula[2 * i + i] && matricula[2 * i + i] <= 'Z' &&
               'A' <= matricula[2 * i + i + 1] &&
               matricula[2 * i + i + 1] <= 'Z'));
    }
    return abs(r) == 1;
}

/**
 * Funcao que trata dos erros de adicionar um carro e mostra os erros
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @param matricula matricula do carro
 * @param dataEntrada data de entrada do carro
 * @param horaEntrada hora de entrada do carro
 * @param ultimaData ultima data do sistema
 * @param ultimaHora ultima hora do sistema
 * @return 1 se nao houver erros, 0 caso contrario
 */
int tratarErrosAdicionarCarro(NodeParque *parques, char *nomeParque,
                              char *matricula, Data dataEntrada,
                              Hora horaEntrada, Data ultimaData,
                              Hora ultimaHora) {
    NodeParque *auxParque = parques;
    NodeCarro *auxNodeCarro;
    int flag1 = 0;  // verifica se o parque existe
    int flag2 = 0;  // verifica se o parque esta cheio
    unsigned long index;

    while (auxParque != NULL) {
        if (strcmp(auxParque->parque.nome, nomeParque) == 0) {
            flag1 = 1;  // o parque existe
            if (auxParque->parque.lugaresOcupados ==
                auxParque->parque.capacidade) {
                flag2 = 1;
            }
            break;
        }
        auxParque = auxParque->next;
    }

    if (flag1 == 0) {
        printf("%s: no such parking.\n", nomeParque);
        return 0;
    }
    if (flag2 == 1) {
        printf("%s: parking is full.\n", nomeParque);
        return 0;
    }
    if (matriculaValida(matricula) == 0) {
        printf("%s: invalid licence plate.\n", matricula);
        return 0;
    }

    auxParque = parques;

    while (auxParque != NULL) {
        index = hash(matricula, auxParque->parque.carros->size);

        auxNodeCarro = auxParque->parque.carros->buckets[index];

        while (auxNodeCarro != NULL) {
            if (strcmp(auxNodeCarro->carro.Matricula, matricula) == 0 &&
                auxNodeCarro->carro.estado == DENTRO) {
                printf("%s: invalid vehicle entry.\n", matricula);
                return 0;
            }
            auxNodeCarro = auxNodeCarro->next;
        }
        auxParque = auxParque->next;
    }

    if ((dataValida(dataEntrada, horaEntrada) == 0) ||
        (dataEhRecente(ultimaData, ultimaHora, dataEntrada, horaEntrada) ==
         0)) {
        printf("invalid date.\n");
        return 0;
    }

    return 1;
}

/**
 * Funcao que trata dos erros de remover um carro e mostra os erros
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @param matricula matricula do carro
 * @param dataEntrada data de entrada do carro
 * @param horaEntrada hora de entrada do carro
 * @param ultimaData ultima data do sistema
 * @param ultimaHora ultima hora do sistema
 * @return 1 se nao houver erros, 0 caso contrario
 */
int tratarErrosRemoverCarro(NodeParque *parques, char *nomeParque,
                            char *matricula, Data dataEntrada, Hora horaEntrada,
                            Data ultimaData, Hora ultimaHora) {
    NodeParque *auxParque = parques;
    NodeCarro *auxNodeCarro;
    int flag1 = 0;  // verifica se o parque existe
    int flag2 = 0;  // verifica se o carro esta no parque
    unsigned long index;

    while (auxParque != NULL) {
        if (strcmp(auxParque->parque.nome, nomeParque) == 0) {
            flag1 = 1;  // o parque existe
            index = hash(matricula, auxParque->parque.carros->size);

            auxNodeCarro = auxParque->parque.carros->buckets[index];

            while (auxNodeCarro != NULL) {
                if (strcmp(auxNodeCarro->carro.Matricula, matricula) == 0 &&
                    auxNodeCarro->carro.estado == DENTRO) {
                    flag2 = 1;
                    break;
                }
                auxNodeCarro = auxNodeCarro->next;
            }
            break;
        }
        auxParque = auxParque->next;
    }
    if (flag1 == 0) {
        printf("%s: no such parking.\n", nomeParque);
        return 0;
    }

    if (matriculaValida(matricula) == 0) {
        printf("%s: invalid licence plate.\n", matricula);
        return 0;
    }

    if (flag2 == 0) {
        printf("%s: invalid vehicle exit.\n", matricula);
        return 0;
    }

    if ((dataValida(dataEntrada, horaEntrada) == 0) ||
        (dataEhRecente(ultimaData, ultimaHora, dataEntrada, horaEntrada) ==
         0)) {
        printf("invalid date.\n");
        return 0;
    }

    return 1;
}

/**
 * Funcao que trata dos erros de listar as entradas e saidas de um carro e
 * mostra os erros
 * @param parques lista de parques
 * @param matricula matricula do carro
 * @return 1 se nao houver erros, 0 caso contrario
 */
int tratarErrosListarEntradasSaidas(NodeParque *parques, char *matricula) {
    NodeParque *auxParque = parques;
    NodeCarro *auxNodeCarro;
    int flag = 0;
    unsigned long index;

    if (matriculaValida(matricula) == 0) {
        printf("%s: invalid licence plate.\n", matricula);
        return 0;
    }

    while (auxParque != NULL) {
        index = hash(matricula, auxParque->parque.carros->size);
        auxNodeCarro = auxParque->parque.carros->buckets[index];

        while (auxNodeCarro != NULL) {
            if (strcmp(auxNodeCarro->carro.Matricula, matricula) == 0) {
                flag = 1;
                break;
            }
            auxNodeCarro = auxNodeCarro->next;
        }
        auxParque = auxParque->next;
    }

    if (flag == 0) {
        printf("%s: no entries found in any parking.\n", matricula);
        return 0;
    }
    return 1;
}
