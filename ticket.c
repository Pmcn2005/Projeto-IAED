/**
 * @brief Ficheiro que contem as funcoes relacionadas com os tickets
 * @file ticket.c
 * @author Pedro Nunes ist1109368
 */

#include "funcs.h"

/**
 * Funcao que cria um ticket
 * @param char Matricula do carro
 * @param Data data de saida
 * @param Hora hora de saida
 * @param float valor pago
 * @return ticket
 */
Ticket criarTicket(char *Matricula, Data dataSaida, Hora horaSaida,
                   float valorPago) {
    Ticket ticket;

    ticket.Matricula = strdup(Matricula);
    ticket.dataSaida = dataSaida;
    ticket.horaSaida = horaSaida;
    ticket.valorPago = valorPago;

    return ticket;
}

/**
 * Funcao que cria um node de ticket
 * @param Ticket ticket
 * @return NodeTicket
 */
NodeTicket *criarNodeTicket(Ticket ticket) {
    NodeTicket *newNode = (NodeTicket *)malloc(sizeof(NodeTicket));

    newNode->ticket = ticket;
    newNode->next = NULL;

    return newNode;
}

/**
 * Funcao que adiciona um ticket a lista de tickets
 * @param NodeTicket lista de tickets
 * @param Ticket ticket a adicionar
 */
void adicionarTicket(NodeTicket **tickets, Ticket ticket) {
    NodeTicket *newNode = criarNodeTicket(ticket);
    NodeTicket *current;

    if (*tickets == NULL) {
        *tickets = newNode;
    } else {
        current = *tickets;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}