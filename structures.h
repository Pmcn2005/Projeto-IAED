/**
 * @brief Ficheiro que contem as estruturas de dados
 * @file structures.h
 * @author Pedro Nunes ist1109368
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#define MAXPARQUES 20
#define FORA 0
#define DENTRO 1
#define TAMANHO_MATRICULA 9

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct hora {
    int hora;
    int minuto;
} Hora;

typedef struct carro {
    char *Matricula;  // EX: AA-00-00
    Data dataEntrada;
    Hora horaEntrada;
    Data dataSaida;
    Hora horaSaida;
    int estado;  // FORA = 0, DENTRO = 1
    float valorPago;
} Carro;

typedef struct nodeCarro {
    Carro carro;
    struct nodeCarro *next;
} NodeCarro;

typedef struct {
    NodeCarro **buckets;
    int size;
} CarroHashTable;

typedef struct ticket {
    char *Matricula;
    Data dataSaida;
    Hora horaSaida;
    float valorPago;
} Ticket;

typedef struct nodeTicket {
    Ticket ticket;
    struct nodeTicket *next;
} NodeTicket;

typedef struct parque {
    char *nome;
    int capacidade;
    int lugaresOcupados;
    CarroHashTable *carros;
    NodeTicket *tickets;
    float valor15Min;
    float valor30Apos1Hora;
    float valorMaximoDia;
} Parque;

typedef struct nodeParque {
    Parque parque;
    struct nodeParque *next;
} NodeParque;

#endif  // _STRUCTURES_H_